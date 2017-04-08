#include "LogisticRegression.h"

LogisticRegression::LogisticRegression(string path){
    Matrix<double> matrix;
    matrix.load(path);        //格式为 [ x y ]
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
double LogisticRegression::estimation_under_current_theta(Vector<double> &x){
    return 1/(1+ exp(-theta.dot(x)));
}
void LogisticRegression::batch_gradient_descent(){
    iter_cnt = 100000;
    double error_sum , h ;
    Vector<double> errors(y.size());
    while(iter_cnt > 0 ){
        for(unsigned int i = 0; i< y.size(); ++i){          //计算每组的误差
            h = estimation_under_current_theta(x_matrix[i]);
            errors[i] = h - y[i];
        }
        for(int j=0;j<demision;++j){                        //更新
            error_sum = 0;
            for(unsigned int i = 0; i< y.size(); ++i)       //计算误差和
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
void LogisticRegression::print_theta(){
    cout<<theta<<endl;
}
void test_LogisticRegression(){
    LogisticRegression lr("logistic_tumor_size_data.txt");
    lr.batch_gradient_descent();
    lr.print_theta();
    Vector<double> test(2,1);
    test[1] = 5.4;
    cout<<lr.estimation_under_current_theta(test)<<endl;
    test[1] = 5.6;
    cout<<lr.estimation_under_current_theta(test)<<endl;
}
