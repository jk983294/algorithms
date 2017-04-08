#include "NeuralNetwork.h"

void MakeData(string dataFile, int numLines)
{
    double weights[] = { -0.1, 0.2, -0.3, 0.4, -0.5,
        0.6, -0.7, 0.8, -0.9, 1.0,
        -1.1, 1.2, -1.3, 1.4, -1.5,
        1.6, -1.7, 1.8, -1.9, 2.0,
        -0.5, 0.6, -0.7, 0.8, -0.9,
        1.5, -1.4, 1.3,
        -1.2, 1.1, -1.0,
        0.9, -0.8, 0.7,
        -0.6, 0.5, -0.4,
        0.3, -0.2, 0.1,
        0.1, -0.3, 0.6 };
    int w_size = sizeof(weights)/sizeof(double);
    vector<double> w(&weights[0],&weights[w_size]);
    NeuralNetwork nn(4, 5, 3);
    nn.SetWeights(w);

    ofstream ofs(dataFile);
    for (int i = 0; i < numLines; ++i){
        vector<double> inputs(4);
        for (unsigned int j = 0; j < inputs.size(); ++j)
            inputs[j] = 1 + rand()%10;

        vector<double> outputs = nn.ComputeOutputs(inputs);

        string color = "";
        int idx = max_index(outputs);
        if (idx == 0) { color = "red"; }
        else if (idx == 1) { color = "green"; }
        else if (idx == 2) { color = "blue"; }
        ofs<<inputs[0]<<" "<<inputs[1]<<" "<<inputs[2]<<" "<<inputs[3]<<" "<<color<<endl;
    }
    ofs.close();

} // MakeData
void MakeTrainAndTest(string file, vector<vector<double> > &trainMatrix, vector<vector<double> > &testMatrix)
{
    int numLines = 0;
    ifstream ifs (file);
    string line;
    while (getline(ifs,line))
        ++numLines;

    int numTrain = (int)(0.80 * numLines);
    int numTest = numLines - numTrain;

    vector<vector<double> > allData(numLines);  // could use Helpers.MakeMatrix here
    for (unsigned int i = 0; i < allData.size(); ++i)
        allData[i].resize(7);                   // (x0, x1, x2, x3), (y0, y1, y2)

    ifs.clear();                                //假若当前文件流的状态是eof，再移动读指针seekg()，将不起作用，必须先调用clear清除eof状态，才能使用seekg移动写指针
    ifs.seekg(0,ios::beg);
    int row = 0;
    while (getline(ifs , line)){
        stringstream ss(line);
        ss>>allData[row][0]>>allData[row][1]>>allData[row][2]>>allData[row][3]>>line;
        for (int i = 0; i < 4; ++i)
            allData[row][i] = 0.25 * allData[row][i] - 1.25;    // scale input data to [-1.0, +1.0]

        if (line == "red") { allData[row][4] = 1.0; allData[row][5] = 0.0; allData[row][6] = 0.0; }
        else if (line == "green") { allData[row][4] = 0.0; allData[row][5] = 1.0; allData[row][6] = 0.0; }
        else if (line == "blue") { allData[row][4] = 0.0; allData[row][5] = 0.0; allData[row][6] = 1.0; }
        ++row;
    }
    ifs.close();
    random_shuffle(allData.begin(), allData.end());
    for( int i = 0; i < numTrain; ++i)
        trainMatrix.push_back(allData[i]);
    for( int i = numTrain; i < numLines; ++i)
        testMatrix.push_back(allData[i]);
} // MakeTrainAndTest
void test_nn(){
    cout<<"Begin neural network classification demo"<<endl
        <<"Goal is to predict/classify color based on four numeric inputs"<<endl;
    cout<<"Creating 100 lines of raw data"<<endl;
    string dataFile = "colors.txt";
    MakeData(dataFile, 100);

    vector<vector<double> > trainMatrix , testMatrix;
    cout<<"Generating train and test matrices using an 80%-20% split"<<endl;
    MakeTrainAndTest(dataFile,  trainMatrix,  testMatrix);

    cout<<"Creating 4-input 5-hidden 3-output neural network"<<endl;
    NeuralNetwork nn(4, 5, 3);

    cout<<"Training to find best neural network weights using PSO with cross entropy error"<<endl;
    vector<double> bestWeights = nn.Train(trainMatrix);
    cout<<"Best weights found:"<<bestWeights<<endl;

    cout<<"Loading best weights into neural network"<<endl;
    nn.SetWeights(bestWeights);

    cout<<"Analyzing the neural network accuracy on the test data"<<endl;
    double accuracy = nn.Test(testMatrix);
    cout<<"Prediction accuracy = " <<accuracy<<endl;
    cout<<"End neural network classification demo"<<endl;
}
double NeuralNetwork::Test(vector<vector<double> > &testMatrix){
    // assumes that weights have been set using SetWeights
    int numCorrect = 0;
    int numWrong = 0;

    for (unsigned int i = 0; i < testMatrix.size(); ++i){ // walk thru each test case. looks like (6.9 3.2 5.7 2.3) (0 0 1)  where the parens are not really there
        vector<double> currInputs(4);
        currInputs[0] = testMatrix[i][0]; currInputs[1] = testMatrix[i][1]; currInputs[2] = testMatrix[i][2]; currInputs[3] = testMatrix[i][3];
        vector<double> currOutputs(3);
        currOutputs[0] = testMatrix[i][4]; currOutputs[1] = testMatrix[i][5]; currOutputs[2] = testMatrix[i][6]; // not really necessary
        vector<double> currPredicted = ComputeOutputs(currInputs); // outputs are in softmax form -- each between 0.0, 1.0 representing a prob and summing to 1.0
        // use winner-takes all -- highest prob of the prediction
        int indexOfLargest = max_index(currPredicted);
        if (i <= 3){ // just a few for demo purposes
            cout<<"-----------------------------------"<<endl<<"Input:     "<<endl;
            cout<<currInputs<<endl<<"Output:    "<<endl<<currOutputs<<endl;
            if (currOutputs[0] == 1.0) cout<<"(red)"<<endl;
            else if (currOutputs[1] == 1.0) cout<<"(green)"<<endl;
            else  cout<<"(blue)"<<endl;
            cout<<"Predicted: "<<currPredicted;
            if (indexOfLargest == 0) cout<<"(red)"<<endl;
            else if (indexOfLargest == 1) cout<<"(green)"<<endl;
            else cout<<"(blue)"<<endl;

            if (currOutputs[indexOfLargest] == 1)    cout<<"correct "<<endl;
            else cout<<"wrong "<<endl;
            cout<<"-----------------------------------"<<endl;
        }

        if (currOutputs[indexOfLargest] == 1)    ++numCorrect;
        else    ++numWrong;
    }
    cout<<"......"<<endl;

    double percentCorrect = (numCorrect * 1.0) / (numCorrect + numWrong);
    cout<<"\nCorrect = "<<numCorrect<<endl;
    cout<<"\nWrong = "<<numWrong<<endl;
    return percentCorrect;
}
vector<double> NeuralNetwork::Train(vector<vector<double> > &trainMatrix){
    int numWeights = (numInput * numHidden) + (numHidden * numOutput) + numHidden + numOutput;
    //double[] currWeights = new double[numWeights];

    // use PSO to seek best weights
    int numberParticles = 10;
    int numberIterations = 500;
    int iteration = 0;
    int Dim = numWeights; // number of values to solve for
    double minX = -5.0; // for each weight
    double maxX = 5.0;

    vector<Particle> swarm(numberParticles);
    vector<double> bestGlobalPosition(Dim); // best solution found by any particle in the swarm. implicit initialization to all 0.0
    double bestGlobalFitness = 10e10; // smaller values better

    double minV = -0.1 * maxX;  // velocities
    double maxV = 0.1 * maxX;

    for (unsigned int i = 0; i < swarm.size(); ++i){ // initialize each Particle in the swarm with random positions and velocities
        vector<double> randomPosition(Dim);
        for (unsigned int j = 0; j < randomPosition.size(); ++j){
            double lo = minX;        double hi = maxX;
            randomPosition[j] = (hi - lo) * ((double)rand()/RAND_MAX) + lo;
        }

        double fitness = CrossEntropy(trainMatrix, randomPosition); // smaller values better
        vector<double> randomVelocity(Dim);

        for (unsigned int j = 0; j < randomVelocity.size(); ++j){
            double lo = -1.0 * abs(maxX - minX);
            double hi = abs(maxX - minX);
            randomVelocity[j] = (hi - lo) * ((double)rand()/RAND_MAX) + lo;
        }
        swarm[i].set(randomPosition, fitness, randomVelocity, randomPosition, fitness);

        // does current Particle have global best position/solution?
        if (swarm[i].fitness < bestGlobalFitness){
            bestGlobalFitness = swarm[i].fitness;
            bestGlobalPosition = swarm[i].position;
        }
    } // initialization

    double w = 0.729;       // inertia weight.
    double c1 = 1.49445;    // cognitive/local weight
    double c2 = 1.49445;    // social/global weight
    double r1, r2;          // cognitive and social randomizations

    cout<<"Entering main PSO weight estimation processing loop"<<endl;
    while (iteration < numberIterations)
    {
        ++iteration;
        vector<double> newVelocity(Dim); vector<double> newPosition(Dim);
        double newFitness;

        for (unsigned int i = 0; i < swarm.size(); ++i){                // each Particle
            Particle &currP = swarm[i];
            for (unsigned int j = 0; j < currP.velocity.size(); ++j){   // each x value of the velocity
                r1 = ((double)rand()/RAND_MAX);
                r2 = ((double)rand()/RAND_MAX);
                newVelocity[j] = (w * currP.velocity[j]) +
                    (c1 * r1 * (currP.bestPosition[j] - currP.position[j])) +
                    (c2 * r2 * (bestGlobalPosition[j] - currP.position[j]));    // new velocity depends on old velocity, best position of parrticle, and best position of any particle

                if (newVelocity[j] < minV)    newVelocity[j] = minV;
                else if (newVelocity[j] > maxV)    newVelocity[j] = maxV;       // crude way to keep velocity in range
            }
            currP.velocity = newVelocity;

            for (unsigned int j = 0; j < currP.position.size(); ++j){
                newPosition[j] = currP.position[j] + newVelocity[j];            // compute new position
                if (newPosition[j] < minX)    newPosition[j] = minX;
                else if (newPosition[j] > maxX)    newPosition[j] = maxX;
            }
            currP.position = newPosition;

            newFitness = CrossEntropy(trainMatrix, newPosition);                // compute error of the new position
            currP.fitness = newFitness;
            if (newFitness < currP.bestFitness){ // new particle best?
                currP.bestPosition = newPosition;
                currP.bestFitness = newFitness;
            }

            if (newFitness < bestGlobalFitness){ // new global best?
                bestGlobalPosition = newPosition;
                bestGlobalFitness = newFitness;
            }
        } // each Particle
    } // while

    cout<<"Processing complete"<<endl;
    cout<<"Final best (smallest) cross entropy error = "<<bestGlobalFitness<<endl;
    return bestGlobalPosition;
}
double NeuralNetwork::CrossEntropy(vector<vector<double> > &trainData, vector<double> &weights){
    // how good (cross entropy) are weights? CrossEntropy is error so smaller values are better
    SetWeights(weights); // load the weights and biases to examine

    double sce = 0.0; // sum of cross entropy
    for (unsigned int i = 0; i < trainData.size(); ++i){ // walk thru each training case. looks like (6.9 3.2 5.7 2.3) (0 0 1)  where the parens are not really there
        vector<double> currInputs(4); currInputs[0] = trainData[i][0]; currInputs[1] = trainData[i][1]; currInputs[2] = trainData[i][2]; currInputs[3] = trainData[i][3];
        vector<double> currExpected(3); currExpected[0] = trainData[i][4]; currExpected[1] = trainData[i][5]; currExpected[2] = trainData[i][6]; // not really necessary
        vector<double> currOutputs = ComputeOutputs(currInputs); // run the jnputs through the neural network
        // compute ln of each nn output (and the sum)
        double currSum = 0.0;
        for (unsigned int j = 0; j < currOutputs.size(); ++j)
            if (currExpected[j] != 0.0)    currSum += currExpected[j] * log(currOutputs[j]);
        sce += currSum; // accumulate
    }
    return -sce;
}
vector<double> NeuralNetwork::ComputeOutputs(vector<double> currInputs){
    if (inputs.size() != numInput){ vector<double> a;    cout<<"inputs dimension exception!!!"<<endl;    return a;}

    for (int i = 0; i < numHidden; ++i)        ihSums[i] = 0.0;
    for (int i = 0; i < numOutput; ++i)        hoSums[i] = 0.0;
    // copy
    for (unsigned int i = 0; i < currInputs.size(); ++i)        inputs[i] = currInputs[i];

    for (int j = 0; j < numHidden; ++j) // compute input-to-hidden sums
        for (int i = 0; i < numInput; ++i)
            ihSums[j] += inputs[i] * ihWeights[i][j];
    // add biases to input-to-hidden sums
    for (int i = 0; i < numHidden; ++i)  ihSums[i] += ihBiases[i];
    // determine input-to-hidden output
    for (int i = 0; i < numHidden; ++i){
        //ihOutputs[i] = StepFunction(ihSums[i]); // step function
        ihOutputs[i] = SigmoidFunction(ihSums[i]);
        //ihOutputs[i] = TanhFunction(ihSums[i]);
    }
    for (int j = 0; j < numOutput; ++j)   // compute hidden-to-output sums
        for (int i = 0; i < numHidden; ++i)
            hoSums[j] += ihOutputs[i] * hoWeights[i][j];
    // add biases to input-to-hidden sums
    for (int i = 0; i < numOutput; ++i)  hoSums[i] += hoBiases[i];

    //Sigmoid一般用于预测值
//     for (int i = 0; i < numOutput; ++i)   // determine hidden-to-output result
//         outputs[i] = SigmoidFunction(hoSums[i]);  // step function
//     vector<double> result = outputs;

    //Softmax一般用于分类
    vector<double> result = Softmax(hoSums);

    return result;
}
vector<double> NeuralNetwork::Softmax(vector<double> &hoSums){
    // determine max
    double max = hoSums[0];
    for (unsigned int i = 0; i < hoSums.size(); ++i)
        if (hoSums[i] > max) max = hoSums[i];
    // determine scaling factor (sum of exp(eachval - max)
    double scale = 0.0;
    for (unsigned int i = 0; i < hoSums.size(); ++i)
        scale += exp(hoSums[i] - max);
    vector<double> result;    result.resize(hoSums.size());
    for (unsigned int i = 0; i < hoSums.size(); ++i)
        result[i] = exp(hoSums[i] - max) / scale;
    return result;
}
void NeuralNetwork::SetWeights(vector<double> weights){
    int numWeights = (numInput * numHidden) + (numHidden * numOutput) + numHidden + numOutput;
    if (weights.size() != numWeights){ cout<<"dimension exception!!!"<<endl;    return;}

    int k = 0; // points into weights param
    for (int i = 0; i < numInput; ++i)
        for (int j = 0; j < numHidden; ++j)
            ihWeights[i][j] = weights[k++];
    for (int i = 0; i < numHidden; ++i)
        ihBiases[i] = weights[k++];
    for (int i = 0; i < numHidden; ++i)
        for (int j = 0; j < numOutput; ++j)
            hoWeights[i][j] = weights[k++];
    for (int i = 0; i < numOutput; ++i)
        hoBiases[i] = weights[k++];
}

NeuralNetwork::NeuralNetwork(int numInput, int numHidden, int numOutput){
    this->numInput = numInput;
    this->numHidden = numHidden;
    this->numOutput = numOutput;

    inputs.resize(numInput);
    ihOutputs.resize(numHidden);
    outputs.resize(numOutput);
    ihSums.resize(numHidden);
    ihBiases.resize(numHidden);
    hoSums.resize(numOutput);
    hoBiases.resize(numOutput);
    ihWeights.resize(numInput);
    hoWeights.resize(numHidden);
    for (int i = 0; i < numInput; ++ i)
        ihWeights[i].resize(numHidden);
    for (int i = 0; i < numHidden; ++ i)
        hoWeights[i].resize(numOutput);
}
double NeuralNetwork::SigmoidFunction(double x){
    if (x < -45.0) return 0.0;
    else if (x > 45.0) return 1.0;
    else return 1.0 / (1.0 + exp(-x));
}
double NeuralNetwork::StepFunction(double x){
    if (x > 0.0) return 1.0;
    else return 0.0;
}
int max_index(vector<double> &array){
    if(array.size() > 0){
        int idx = 0;    double max_value = array[0];
        for (unsigned int i = 1; i < array.size(); ++ i) {
            if(max_value < array[i]){
                max_value = array[i];
                idx = i;
            }
        }
        return idx;
    }return -1;
}
