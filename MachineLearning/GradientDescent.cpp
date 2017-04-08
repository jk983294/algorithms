#include "GradientDescent.h"

GradientDescent::GradientDescent(string path){
    Matrix<double> matrix;
    matrix.load(path);                  //格式为 [ x y ]
    demision = matrix.get_columns_number();
    x_cnt = demision - 1;
    y = matrix.arrange_column(demision -1);
    theta.resize(demision, 0);
    Vector<double> x(demision, 1);
    for (int i = 0; i < matrix.get_rows_number(); ++i){
        for (int j = 0; j < x_cnt; ++j)
            x[j+1] = matrix[i][j];
        x_matrix.push_back(x);
    }
    learning_rate = 10e-4;
    precision = 10e-3;
}
double GradientDescent::estimation_under_current_theta(Vector<double> &x){
    return theta.dot(x);
}
void GradientDescent::batch_gradient_descent(){
    iter_cnt = 1000000;
    double error_sum , h ;
    Vector<double> errors(y.size());
    while(iter_cnt > 0 ){
        for(unsigned int i = 0; i< y.size(); ++i){      //计算每组的误差
            h = estimation_under_current_theta(x_matrix[i]);
            errors[i] = h - y[i];
        }
        for(int j=0;j<demision;++j){                    //更新
            error_sum = 0;
            for(unsigned int i = 0; i< y.size(); ++i)   //计算误差和
                error_sum += errors[i] * x_matrix[i][j];
            theta[j] -= learning_rate*error_sum;
        }
        errors = errors * errors;
        precision = errors.calculate_sum();
        if(precision < 10e-6){
            cout<<iter_cnt<<" "<<precision<<endl;
            break;
        }
        --iter_cnt;
    }
}
void GradientDescent::stochastic_gradient_descent(){
    iter_cnt = 10000000;
    double error_single , h ;
    Vector<double> errors(y.size());
    while(iter_cnt > 0 ){
        for(unsigned int i = 0; i< y.size(); ++i){      //计算每组的误差
            h = estimation_under_current_theta(x_matrix[i]);
            error_single = h - y[i];
            for(int j=0;j<demision;++j){                //更新
                theta[j] -= learning_rate* error_single * x_matrix[i][j];
            }
        }

        for(unsigned int i = 0; i< y.size(); ++i){      //计算每组的误差
            h = estimation_under_current_theta(x_matrix[i]);
            errors[i] = h - y[i];
        }
        precision = (errors * errors).calculate_sum();
        if(precision < 10e-6){
            cout<<iter_cnt<<" "<<precision<<endl;
            break;
        }
        --iter_cnt;
    }
}
void GradientDescent::print_theta(){
    cout<<theta<<endl;
}
void test_GradientDescent(){
    GradientDescent gd("gradient_descent_data.txt");
    gd.batch_gradient_descent();
    gd.print_theta();

    GradientDescent gd1("gradient_descent_data.txt");
    gd1.stochastic_gradient_descent();
    gd1.print_theta();
}
