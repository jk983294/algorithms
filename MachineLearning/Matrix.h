#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <climits>
#include <cmath>

#include "Vector.h"
using namespace std;

template <class Type>
class Matrix
{
public:
/// Default constructor.
    explicit Matrix(void);                          //It creates a matrix with zero rows and zero columns.
    explicit Matrix(const unsigned int& new_rows_number, const unsigned int& new_columns_number);
    explicit Matrix(const unsigned int& new_rows_number, const unsigned int& new_columns_number, const Type& type);
    explicit Matrix(const std::string& filename);
    Matrix(const Matrix& other_matrix);
/// Destructor.
    ~Matrix(void);

///计算函数  calculate
    /// 计算矩阵的迹,即主对角线上元素之和
    double calculate_trace(void) const;
    /// 计算每列的均值
    Vector<double> calculate_mean(void) const;
    /// 计算指定列的均值
    Vector<double> calculate_mean(const Vector<unsigned int>& column_indices) const;
    /// 计算指定列的某些行的均值
    Vector<double> calculate_mean(const Vector<unsigned int>& row_indices, const Vector<unsigned int>& column_indices) const;
    /// 计算矩阵列的均值和方差,两个Vector，一个是均值，一个是方差
    Vector< Vector<double> > calculate_mean_standard_deviation(void) const;
    Vector< Vector<double> > calculate_mean_standard_deviation(const Vector<unsigned int>& column_indices) const;
    Vector< Vector<double> > calculate_mean_standard_deviation(const Vector<unsigned int>& row_indices, const Vector<unsigned int>& column_indices) const;
    /// 计算矩阵列的最大最小值,两个Vector，一个是最小值，一个是最大值
    Vector< Vector<Type> > calculate_minimum_maximum(void) const;
    Vector< Vector<Type> > calculate_minimum_maximum(const Vector<unsigned int>& column_indices) const;
    Vector< Vector<Type> > calculate_minimum_maximum(const Vector<unsigned int>& row_indices, const Vector<unsigned int>& column_indices) const;
    /// 计算每列的统计数据,4个Vector,最小最大值，均值方差
    Vector< Vector<double> > calculate_statistics(void) const;
    /// 计算每一列的柱状图，主vector是每列统计数据，subvector包含该列的频率和中心,bins_number是每列的等长区间个数
    Vector< Vector< Vector<Type> > > calculate_histogram(const unsigned int& bins_number) const;
    /// bins_number(10).
    Vector< Vector< Vector<Type> > > calculate_histogram(void) const;
    /// 每列数据按照指定的均值方差进行放缩
    void scale_mean_standard_deviation_self();      //自己根据每列的均值方差进行缩放
    void scale_mean_standard_deviation(const Vector<double>& mean, const Vector<double>& standard_deviation) const;
    void unscale_mean_standard_deviation(const Vector<double>& mean, const Vector<double>& standard_deviation) const;
    /// 每列数据按照指定的最大最小值进行放缩
    void scale_minimum_maximum_self();              //自己根据每列的最大最小值进行缩放
    void scale_minimum_maximum(const Vector<double>& minimum, const Vector<double>& maximum) const;
    void unscale_minimum_maximum(const Vector<double>& minimum, const Vector<double>& maximum) const;
    /// 获得指定[minimum, maximum] 中的均匀随机数
    double calculate_random_uniform(const double& minimum, double maximum) const;
    /// 获得指定[mean, standard_deviation] 中的正态分布随机数
    double calculate_random_normal(const double& mean, double standard_deviation) const;
    /// 返回最小值的坐标(x,y)
    Vector<unsigned int> calculate_minimal_indices(void) const;
    /// 返回最大值的坐标(x,y)
    Vector<unsigned int> calculate_maximal_indices(void) const;
    /// 返回最小最大值的坐标(x,y)
    Vector< Vector<unsigned int> > calculate_minimal_maximal_indices(void) const;
    /// 计算和另一个矩阵的误差平方和
    double calculate_sum_squared_error(const Matrix<double>& other_matrix) const;
    /// 计算和一个向量的按列 误差平方和，每列元素减去对应向量位置元素的误差平方和
    double calculate_sum_squared_error(const Vector<double>& vector) const;
    /// 计算每行的均方值=sqrt ( sigma(data[i][j] * data[i][j]) )
    Vector<double> calculate_rows_norm(void) const;
    /// 返回矩阵的绝对值
    Matrix<Type> calculate_absolute_value(void) const;
    /// 返回矩阵的转置
    Matrix<Type> calculate_transpose(void) const;
    /// 计算矩阵的行列式     |M|
    Type calculate_determinant(void) const;
    /// 计算矩阵的余子式矩阵 求矩阵逆的时候用
    Matrix<Type> calculate_cofactor(void) const;
    /// 计算矩阵的逆矩阵 A*A-1 = E
    Matrix<Type> calculate_inverse(void) const;
    /// 计算矩阵乘以向量得到向量
    Vector<Type> dot(const Vector<Type>& vector) const;
    /// 计算矩阵乘以矩阵得到矩阵
    Matrix<Type> dot(const Matrix<Type>& other_matrix) const;
    /// @todo This product is also known as the Kronecker product.
    Matrix<Type> direct(const Matrix<Type>& other_matrix) const;

/// get method.
    const unsigned int& get_rows_number(void) const;
    const unsigned int& get_columns_number(void) const;
    /// 获得指定行和列的子矩阵
    Matrix<Type> arrange_submatrix(const Vector<unsigned int>& row_indices, const Vector<unsigned int>& column_indices) const;
    /// 获得指定行的子矩阵
    Matrix<Type> arrange_submatrix_rows(const Vector<unsigned int>& row_indices) const;
    /// 获得指定列的子矩阵
    Matrix<Type> arrange_submatrix_columns(const Vector<unsigned int>& column_indices) const;
    /// 获得指定列的向量
    Vector<Type> arrange_row(const unsigned int& i) const;
    /// 获得指定行中的某些列的向量
    Vector<Type> arrange_row(const unsigned int& row_index, const Vector<unsigned int>& column_indices) const;
    /// 获得指定列的向量
    Vector<Type> arrange_column(const unsigned int& j) const;
    /// 获得指定列的最后dataNum个元素向量
    Vector<Type> arrange_column_range( unsigned int j, int begin, int end)const;
    /// 获得指定列的最后dataNum个元素向量
    Vector<Type> arrange_column_last(const unsigned int& j,const int& dataNum) const;
    /// 获得指定列的向量
    Vector<Type> arrange_column(const unsigned int& j,const unsigned int& begin,const unsigned int& end) const;
    /// 获得指定列中的某些行的的向量
    Vector<Type> arrange_column(const unsigned int& column_index, const Vector<unsigned int>& row_indices) const;
    /// 取对角线元素
    Vector<Type> get_diagonal(void) const;

/// set method.
    void set(void);                                 //全部清零释放数据
    void set(const unsigned int& new_rows_number, const unsigned int& new_columns_number);
    void set(const unsigned int& new_rows_number, const unsigned int& new_columns_number, const Type& value);
    void set(const Matrix& other_matrix);
    void set(const std::string& filename);
    //设置单位矩阵,方阵，对角线全1，其余为0
    void set_identity(const unsigned int& new_size);
    void set_rows_number(const unsigned int& new_rows_number);
    void set_columns_number(const unsigned int& new_columns_number);
    /// 设置row_index指定行的数据为new_row
    void set_row(const unsigned int& row_index, const Vector<Type>& new_row);
    /// 设置row_index指定行的数据为value
    void set_row(const unsigned int& row_index, const Type& value);
    void set_column(const unsigned int& column_index, const Vector<Type>& new_column);
    void set_column(const unsigned int& column_index, const Type& value);
    /// 设置对角线元素
    void set_diagonal(const Type& new_diagonal);
    void set_diagonal(const Vector<Type>& new_diagonal);

    /// This method sets new numbers of rows and columns in the vector.
    void resize(const unsigned int& new_rows_number, const unsigned int& new_columns_number);
    /// 把other_matrix的所有数据拷贝到(row_position,column_position)开始的矩阵中
    void tuck_in(const unsigned int& row_position, const unsigned int& column_position, const Matrix<Type>& other_matrix);

    /// 设置矩阵为对角矩阵(方阵，只有对角线上有非零值)，对角线上的值为new_value
    void initialize_diagonal(const unsigned int& new_size, const Type& new_value);
    void initialize_diagonal(const unsigned int& new_size, const Vector<Type>& new_values);
    /// 对角线元素全部加new_summing_value
    Matrix<Type> sum_diagonal(const Type& new_summing_value) const;
    Matrix<Type> sum_diagonal(const Vector<Type>& new_summing_values) const;
    /// 添加行
    void append_row(const Vector<Type>& new_row);
    /// 添加列
    void append_column(const Vector<Type>& new_column);
    /// 移除指定行
    void subtract_row(const unsigned int& row_index);
    /// 移除指定列
    void subtract_column(const unsigned int& column_index);
    /// 两个矩阵列合并，左边是原矩阵，右边是other_matrix，两矩阵必须等高
    Matrix<Type> get_assembly_columns(const Matrix<Type>& other_matrix) const;

/// 矩阵值初始化
    void initialize(const Type& value) const;       ///矩阵值全部初始化为value
    void initialize_uniform(void) const;            /// 初始化矩阵，元素为均匀[-1,1]随机值
    /// 初始化矩阵，元素为均匀[minimum,maximum]随机值
    void initialize_uniform(const double& minimum, double maximum) const;
    void initialize_uniform(const Matrix<double>& minimum, const Matrix<double>& maximum) const;
    void initialize_normal(void) const;             /// 初始化矩阵，元素为标准正太分布(mean = 0, delta = 1)随机值
    void initialize_normal(const double& mean, double standard_deviation) const;
    void initialize_normal(const Matrix<double>& mean, const Matrix<double>& standard_deviation) const;
    void initialize_identity(void) const;           /// 初始化为单位阵
    /// 初始化对角线元素，其余都为0
    void initialize_diagonal(const Type& value) const;

///运算符重载
    inline Matrix<Type>& operator = (const Matrix<Type>& other_matrix);
    inline Type* operator [] (const unsigned int& i);
    inline const Type* operator [] (const unsigned int& i) const;
    /// Equivalent relational operator between this matrix and other matrix.
    inline bool operator == (const Matrix<Type>& other_matrix) const;
    /// 矩阵所有值都等于value返回true
    inline bool operator == (const Type& value) const;
    /// Not equivalent relational operator between this matrix and other matrix.
    inline bool operator != (const Matrix<Type>& other_matrix) const;
    /// 矩阵中某些值不等于value返回true
    inline bool operator != (const Type& value) const;
    /// 矩阵值全部大于other_matrix
    inline bool operator > (const Matrix<Type>& other_matrix) const;
    inline bool operator > (const Type& value) const;
    /// It produces true if all the elements of this matrix are less than the corresponding elements of the other matrix,
    inline bool operator < (const Matrix<Type>& other_matrix) const;
    inline bool operator < (const Type& value) const;
    inline bool operator >= (const Matrix<Type>& other_matrix) const;
    inline bool operator >= (const Type& value) const;
    inline bool operator <= (const Matrix<Type>& other_matrix) const;
    inline bool operator <= (const Type& value) const;
    inline Matrix<Type> operator + (const Type& scalar) const;
    /// 每行同时加对应的值
    inline Matrix<Type> operator + (const Vector<Type>& vector) const;
    inline Matrix<Type> operator + (const Matrix<Type>& other_matrix) const;
    inline Matrix<Type> operator - (const Type& scalar) const;
    inline Matrix<Type> operator - (const Vector<Type>& vector) const;
    inline Matrix<Type> operator - (const Matrix<Type>& other_matrix) const;
    inline Matrix<Type> operator * (const Type& scalar) const;
    inline Matrix<Type> operator * (const Vector<Type>& vector) const;
    ///对应元素乘，不是矩阵乘
    inline Matrix<Type> operator * (const Matrix<Type>& other_matrix) const;
    inline Matrix<Type> operator / (const Type& scalar) const;
    /// 按列除
    inline Matrix<Type> operator / (const Vector<Type>& vector) const;
    ///对应元素除，不是矩阵除
    inline Matrix<Type> operator / (const Matrix<Type>& other_matrix) const;
    inline void operator += (const Type& value);
    inline void operator += (const Matrix<Type>& other_matrix);
    inline void operator -= (const Type& value);
    inline void operator -= (const Matrix<Type>& other_matrix);
    inline void operator *= (const Type& value);
    ///对应元素乘，不是矩阵乘
    inline void operator *= (const Matrix<Type>& other_matrix);
    inline void operator /= (const Type& value);
    ///对应元素除，不是矩阵除
    inline void operator /= (const Matrix<Type>& other_matrix);

/// 判断函数
    bool empty(void) const;
    bool is_square(void) const;
    bool is_symmetric(void) const;                  //是否是对称矩阵
    bool is_antisymmetric(void) const;              //是否是反对称矩阵
    bool is_diagonal(void) const;                   //是否是对角矩阵
    bool is_scalar(void) const;                     //对角矩阵 对角元素只有相同的值 k*E
    bool is_identity(void) const;                   //是否是单位阵

///持久化
    void print(void) const;
    void load(const std::string& filename);
    void save(const std::string& filename) const;
    std::string to_string(void) const;
    Matrix<std::string> get_string_matrix(void) const;
    Vector<Type> to_vector(void) const;

public:

/// Number of rows in matrix.
unsigned int rows_number;
/// Number of columns in matrix.
unsigned int columns_number;

/// Double pointer to a Type.
Type** data;
};


/// This method re-writes the inputs operator >> for the Vector template.
/// @param is Input stream.
/// @param m Input matrix.
template<typename Type>
inline std::istream& operator >> (std::istream& is, Matrix<Type>& m)
{
    const unsigned int rows_number = m.get_rows_number();
    const unsigned int columns_number = m.get_columns_number();

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            is >> m[i][j];
        }
    }

    return(is);
}


// Output operator

/// This method re-writes the outputs operator << for the Matrix template.
/// @param os Output stream.
/// @param m Output matrix.
template<typename Type>
inline std::ostream& operator << (std::ostream& os, const Matrix<Type>& m)
{
    const unsigned int rows_number = m.get_rows_number();
    const unsigned int columns_number = m.get_columns_number();

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            os << m[i][j] << " ";
        }

        os << std::endl;
    }

    return(os);
}


// Output operator
template<typename Type>
inline std::ostream& operator << (std::ostream& os, const Matrix< Vector<Type> >& m)
{
    const unsigned int rows_number = m.get_rows_number();
    const unsigned int columns_number = m.get_columns_number();

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            os << "subvector_" << i << "_" << j << "\n"
                << m[i][j] << std::endl;
        }
    }

    return(os);
}


// Output operator
template<typename Type>
inline std::ostream& operator << (std::ostream& os, const Matrix< Matrix<Type> >& m)
{
    const unsigned int rows_number = m.get_rows_number();
    const unsigned int columns_number = m.get_columns_number();

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            os << "submatrix_" << i << "_" << j << "\n"
                << m[i][j];
        }
    }
    return(os);
}
template<typename Type>
Matrix<Type>::Matrix(void)
{
    rows_number = 0;
    columns_number = 0;
    data = NULL;
}
template<typename Type>
Matrix<Type>::Matrix(const unsigned int& new_rows_number, const unsigned int& new_columns_number)
{
    if(new_rows_number == 0 && new_columns_number == 0)
    {
        rows_number = 0;
        columns_number = 0;
        data = NULL;
    }
    else if(new_rows_number == 0)
    {
        std::ostringstream buffer;
        buffer << "Number of rows must be greater than zero.\n";
        throw std::logic_error(buffer.str());
    }
    else if(new_columns_number == 0)
    {
        std::ostringstream buffer;
        buffer << "Number of columns must be greater than zero.\n";
        throw std::logic_error(buffer.str());
    }
    else
    {
        rows_number = new_rows_number;
        columns_number = new_columns_number;
        data = new Type*[rows_number];
        data[0] = new Type[rows_number*columns_number];
        for(unsigned int i = 1; i < rows_number; i++)
        {
            data[i] = data[i-1] + columns_number;
        }
    }
}

template<typename Type>
Matrix<Type>::Matrix(const unsigned int& new_rows_number, const unsigned int& new_columns_number, const Type& type)
{
    if(new_rows_number == 0 && new_columns_number == 0)
    {
        rows_number = 0;
        columns_number = 0;
        data = NULL;
    }
    else if(new_rows_number == 0)
    {
        std::ostringstream buffer;
        buffer << "Number of rows must be greater than zero.\n";
        throw std::logic_error(buffer.str());
    }
    else if(new_columns_number == 0)
    {
        std::ostringstream buffer;

        buffer << "Number of columns must be greater than zero.\n";

        throw std::logic_error(buffer.str());
    }
    else
    {
        // Set sizes
        rows_number = new_rows_number;
        columns_number = new_columns_number;

        data = new Type*[new_rows_number];
        data[0] = new Type[rows_number*columns_number];

        for(unsigned int i = 1; i < rows_number; i++)
        {
            data[i] = data[i-1] + columns_number;
        }

        // Initialize
        for(unsigned int i = 0; i < rows_number; i++)
        {
            for(unsigned int j = 0; j < columns_number; j++)
            {
                data[i][j] = type;
            }
        }
    }
}
template<typename Type>
Matrix<Type>::Matrix(const std::string& filename)
{
    rows_number = 0;
    columns_number = 0;
    data = NULL;

    load(filename);
}
template<typename Type>
Matrix<Type>::Matrix(const Matrix& other_matrix)
{
    const unsigned int new_rows_number = other_matrix.rows_number;
    const unsigned int new_columns_number = other_matrix.columns_number;

    data = NULL;

    if(new_rows_number == 0 && new_columns_number == 0)
    {
        rows_number = 0;
        columns_number = 0;
        data = NULL;
    }
    else if(new_rows_number == 0)
    {
        std::ostringstream buffer;
        buffer << "Number of rows must be greater than zero.\n";
        throw std::logic_error(buffer.str());
    }
    else if(new_columns_number == 0)
    {
        std::ostringstream buffer;
        buffer << "Number of columns must be greater than zero.\n";
        throw std::logic_error(buffer.str());
    }
    else
    {
        rows_number = new_rows_number;
        columns_number = new_columns_number;

        data = new Type*[rows_number];
        data[0] = new Type[rows_number*columns_number];

        for(unsigned int i = 1; i < rows_number; i++)
        {
            data[i] = data[i-1] + columns_number;
        }
    }

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] = other_matrix[i][j];
        }
    }
}
template<typename Type>
Matrix<Type>::~Matrix(void)
{
    if(data != NULL)
    {
        delete[] (data[0]);
        delete[] (data);
    }
}
template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator = (const Matrix<Type>& other_matrix)
{
    if(this != &other_matrix)
    {
        if(rows_number != other_matrix.rows_number || columns_number != other_matrix.columns_number) // other sizes
        {
            if(data != NULL)
            {
                delete[] (data[0]);
                delete[] (data);
            }

            rows_number = other_matrix.rows_number;
            columns_number = other_matrix.columns_number;

            data = new Type*[rows_number];
            data[0] = new Type[rows_number*columns_number];

            for(unsigned int i = 1; i < rows_number; i++)
            {
                data[i] = data[i-1] + columns_number;
            }
        }

        for(unsigned int i = 0; i < rows_number; i++)
        {
            for(unsigned int j = 0; j < columns_number; j++)
            {
                data[i][j] = other_matrix[i][j];
            }
        }
    }

    return(*this);
}
template<typename Type>
inline Type* Matrix<Type>::operator [] (const unsigned int& i)
{
    // Return matrix element
    return(data[i]);
}
template<typename Type>
inline const Type* Matrix<Type>::operator [] (const unsigned int& i) const
{
    // Return matrix element
    return(data[i]);
}
template<typename Type>
inline bool Matrix<Type>::operator == (const Matrix<Type>& other_matrix) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] != other_matrix[i][j])
            {
                return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
inline bool Matrix<Type>::operator == (const Type& value) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] != value)
            {
                return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
inline bool Matrix<Type>::operator != (const Matrix<Type>& other_matrix) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] != other_matrix[i][j])
          {
                return(true);
          }
        }
    }

    return(false);
}
template<typename Type>
inline bool Matrix<Type>::operator != (const Type& value) const
{
         for(unsigned int i = 0; i < rows_number; i++)
         {
             for(unsigned int j = 0; j < columns_number; j++)
             {
                 if(data[i][j] != value)
                 {
                     return(true);
                 }
             }
          }
          return false;
}
template<typename Type>
inline bool Matrix<Type>::operator > (const Matrix<Type>& other_matrix) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < rows_number; j++)
        {
            if(data[i][j] <= other_matrix[i][j])
             {
                return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
inline bool Matrix<Type>::operator > (const Type& value) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < rows_number; j++)
        {
            if(data[i][j] <= value)
             {
                return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
inline bool Matrix<Type>::operator < (const Matrix<Type>& other_matrix) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] >= other_matrix[i][j])
            {
              return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
inline bool Matrix<Type>::operator < (const Type& value) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] >= value)
            {
              return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
inline bool Matrix<Type>::operator >= (const Matrix<Type>& other_matrix) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] < other_matrix[i][j])
            {
                return(false);
            }
        }
    }

    return(true);
}

// bool operator >= (const Type&) const

/// Greater than or equal to than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are greater than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.
template<typename Type>
inline bool Matrix<Type>::operator >= (const Type& value) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] < value)
            {
                return(false);
            }
        }
    }

    return(true);
}


// bool operator <= (const Matrix<Type>&) const

/// Less than or equal to relational operator between this matrix and other matrix.
/// It produces true if all the elements of this matrix are less than or equal to the corresponding elements of the
/// other matrix, and false otherwise.
/// @param other_matrix Matrix to be compared with.
template<typename Type>
inline bool Matrix<Type>::operator <= (const Matrix<Type>& other_matrix) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] > other_matrix[i][j])
            {
                return(false);
            }
        }
    }

    return(true);
}


// bool operator <= (const Type&) const

/// Less than or equal to than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are less than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.
template<typename Type>
inline bool Matrix<Type>::operator <= (const Type& value) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] > value)
             {
                return(false);
            }
        }
    }

    return(true);
}


// METHODS

// unsigned int get_rows_number(void) const method

/// This method returns the number of rows in the matrix.
template<typename Type>
const unsigned int& Matrix<Type>::get_rows_number(void) const
{
    return(rows_number);
}


// unsigned int get_columns_number(void) const method

/// This method returns the number of columns in the matrix.
template<typename Type>
const unsigned int& Matrix<Type>::get_columns_number(void) const
{
    return(columns_number);
}


// void set(void) method

/// This method set the numbers of rows and columns of the matrix to zero.
template<typename Type>
void Matrix<Type>::set(void)
{
    if(data != NULL)
    {
        delete[] (data[0]);
        delete[] (data);
    }

    rows_number = 0;
    columns_number = 0;
    data = NULL;
}


// void set(const unsigned int&, const unsigned int&) method

/// This method set new numbers of rows and columns in the matrix.
/// @param new_rows_number Number of rows.
/// @param new_columns_number Number of columns.
template<typename Type>
void Matrix<Type>::set(const unsigned int& new_rows_number, const unsigned int& new_columns_number)
{
    // Control sentence (if debug)

    if(new_rows_number == rows_number && new_columns_number == columns_number)
    {
        // do nothing
    }
    else if(new_rows_number == 0 && new_columns_number == 0)
    {
        set();
    }
    else if(new_rows_number == 0)
    {
    }
    else if(new_columns_number == 0)
    {
    }
    else
    {
        rows_number = new_rows_number;
        columns_number = new_columns_number;

        if(data != NULL)
        {
            delete[] (data[0]);
            delete[] (data);
        }

        data = new Type*[rows_number];
        data[0] = new Type[rows_number*columns_number];

        for(unsigned int i = 1; i < rows_number; i++)
        {
            data[i] = data[i-1] + columns_number;
        }
    }
}


// void set(const unsigned int&, const unsigned int&, const Type&) method

/// This method set new numbers of rows and columns in the matrix.
/// It also initializes all the matrix elements to a given value.
/// @param new_rows_number Number of rows.
/// @param new_columns_number Number of columns.
/// @param value Initialization value.
template<typename Type>
void Matrix<Type>::set(const unsigned int& new_rows_number, const unsigned int& new_columns_number, const Type& value)
{
    if(new_rows_number == 0 && new_columns_number == 0)
    {
        set();
    }
    else if(new_rows_number == 0)
    {
    }
    else if(new_columns_number == 0)
    {
    }
    else
    {
        set(new_rows_number, new_columns_number);
        initialize(value);
    }
}


// void set(const Matrix&) method

/// This method sets all the members of the matrix to those of another matrix.
/// @param other_matrix Setting matrix.
template<typename Type>
void Matrix<Type>::set(const Matrix& other_matrix)
{
}


// void set(const std::string&) method

/// This method sets the members of this object by loading them from a data file.
/// @param filename Name of data file.
template<typename Type>
void Matrix<Type>::set(const std::string& filename)
{
    load(filename);
}


// void set_identity(unsigned int) method

/// This method sets the matrix to be squared, with elements equal one in the diagonal and zero outside the diagonal.
/// @param new_size New number of rows and columns in this matrix.
//设置单位矩阵
template<typename Type>
void Matrix<Type>::set_identity(const unsigned int& new_size)
{
    set(new_size, new_size);
    initialize_identity();
}


// void set_rows_number(unsigned int) method

/// This method sets a new number of rows in the matrix.
/// @param new_rows_number Number of matrix rows.
template<typename Type>
void Matrix<Type>::set_rows_number(const unsigned int& new_rows_number)
{
    if(new_rows_number != rows_number)
    {
        set(new_rows_number, columns_number);
    }
}


// void set_columns_number(unsigned int) method

/// This method sets a new number of columns in the matrix.
/// @param new_columns_number Number of matrix columns.
template<typename Type>
void Matrix<Type>::set_columns_number(const unsigned int& new_columns_number)
{
    if(new_columns_number != columns_number)
    {
        set(rows_number, new_columns_number);
    }
}


// void resize(const unsigned int&, const unsigned int&) method

/// This method sets new numbers of rows and columns in the vector.
/// It does initialize the new matrix with the previous values.
/// @param new_rows_number New number of rows.
/// @param new_columns_number New number of columns.
template<typename Type>
void Matrix<Type>::resize(const unsigned int& new_rows_number, const unsigned int& new_columns_number)
{
    // Resize

    if(new_rows_number == rows_number && new_columns_number == columns_number)
    {
        // Do nothing
    }
    else if(new_rows_number == 0 && new_columns_number == 0)
    {
        rows_number = 0;
        columns_number = 0;

        if(data != NULL)
        {
            delete[] (data[0]);
            delete[] (data);
        }

        data = NULL;
    }
    else if(new_rows_number == 0)
    {
    }
    else if(new_columns_number == 0)
    {
    }
    else
    {
        if(new_rows_number >= rows_number && new_columns_number >= columns_number)
        {
            const Matrix<Type> copy(*this);

            set(new_rows_number, new_columns_number);

            for(unsigned int i = 0; i < copy.get_rows_number(); i++)
            {
                for(unsigned int j = 0; j < copy.get_columns_number(); j++)
                {
                      data[i][j] = copy[i][j];
                }
            }
        }
        else if(new_rows_number >= rows_number && new_columns_number <= columns_number)
        {
            const Matrix<Type> copy(*this);

            set(new_rows_number, new_columns_number);

            for(unsigned int i = 0; i < copy.get_rows_number(); i++)
            {
                for(unsigned int j = 0; j < new_columns_number; j++)
                 {
                    data[i][j] = copy[i][j];
                }
            }
        }
        else if(new_rows_number <= rows_number && new_columns_number >= columns_number)
        {
            const Matrix<Type> copy(*this);

                set(new_rows_number, new_columns_number);

            for(unsigned int i = 0; i < new_rows_number; i++)
            {
                for(unsigned int j = 0; j < copy.get_columns_number(); j++)
                {
                        data[i][j] = copy[i][j];
                }
            }
        }
        else if(new_rows_number <= rows_number && new_columns_number >= columns_number)
        {
            const Matrix<Type> copy(*this);

            set(new_rows_number, new_columns_number);

            for(unsigned int i = 0; i < new_rows_number; i++)
            {
                for(unsigned int j = 0; j < new_columns_number; j++)
                {
                     data[i][j] = copy[i][j];
                }
            }
        }
    }
}



// void tuck_in(const unsigned int&, const unsigned int&, const Matrix<Type>&) const method

/// Tuck in another matrix starting from a given position.
/// @param row_position Insertion row position.
/// @param column_position Insertion row position.
/// @param other_matrix Matrix to be inserted.
template<typename Type>
void Matrix<Type>::tuck_in(const unsigned int& row_position, const unsigned int& column_position, const Matrix<Type>& other_matrix)
{
    const unsigned int other_rows_number = other_matrix.get_rows_number();
    const unsigned int other_columns_number = other_matrix.get_columns_number();

    for(unsigned int i = 0; i < other_rows_number; i++)
    {
        for(unsigned int j = 0; j < other_columns_number; j++)
        {
            data[row_position+i][column_position+j] = other_matrix[i][j];
        }
    }
}


// Matrix<Type> arrange_submatrix(const Vector<unsigned int>&, const Vector<unsigned int>&) const method

/// This method returns a matrix with the values of given rows and columns from this matrix.
/// @param row_indices Indices of matrix rows.
/// @param column_indices Indices of matrix columns.
template<typename Type>
Matrix<Type> Matrix<Type>::arrange_submatrix(const Vector<unsigned int>& row_indices, const Vector<unsigned int>& column_indices) const
{
    const unsigned int row_indices_size = row_indices.size();
    const unsigned int column_indices_size = column_indices.size();

    Matrix<Type> sub_matrix(row_indices_size, column_indices_size);

    unsigned int row_index;
    unsigned int column_index;

    for(unsigned int i = 0; i < row_indices_size; i++)
    {
        row_index = row_indices[i];

        for(unsigned int j = 0; j < column_indices_size; j++)
        {
            column_index = column_indices[j];

            sub_matrix[i][j] = data[row_index][column_index];
        }
    }

    return(sub_matrix);
}


// Matrix<Type> arrange_submatrix_rows(const Vector<unsigned int>&) const method

/// This method returns a submatrix with the values of given rows from this matrix.
/// @param row_indices Indices of matrix rows.
template<typename Type>
Matrix<Type> Matrix<Type>::arrange_submatrix_rows(const Vector<unsigned int>& row_indices) const
{
    const unsigned int row_indices_size = row_indices.size();

    Matrix<Type> sub_matrix(row_indices_size, columns_number);

    unsigned int row_index;

    for(unsigned int i = 0; i < row_indices_size; i++)
    {
        row_index = row_indices[i];

        for(unsigned int j = 0; j < columns_number; j++)
        {
            sub_matrix[i][j] = data[row_index][j];
        }
    }

    return(sub_matrix);
}


// Matrix<Type> arrange_submatrix_columns(const Vector<unsigned int>&) const method

/// This method returns a submatrix with the values of given columns from this matrix.
/// @param column_indices Indices of matrix columns.
template<typename Type>
Matrix<Type> Matrix<Type>::arrange_submatrix_columns(const Vector<unsigned int>& column_indices) const
{
    const unsigned int column_indices_size = column_indices.size();

    Matrix<Type> sub_matrix(rows_number, column_indices_size);

    unsigned int column_index;

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < column_indices_size; j++)
        {
            column_index = column_indices[j];

            sub_matrix[i][j] = data[i][column_index];
        }
    }

    return(sub_matrix);
}


// Vector<Type> arrange_row(const unsigned int&) const method

/// This method returns the row i of the matrix.
/// @param i Index of row.
//返回矩阵某一行
template<typename Type>
Vector<Type> Matrix<Type>::arrange_row(const unsigned int& i) const
{
    Vector<Type> row(columns_number);

    for(unsigned int j = 0; j < columns_number; j++)
    {
        row[j] = data[i][j];
    }

    return(row);
}


// Vector<Type> arrange_row(const unsigned int&, const Vector<unsigned int>&) const method

/// This method returns the row i of the matrix, but only the elements specified by given indices.
/// @param row_index Index of row.
/// @param column_indices Column indices of row.
template<typename Type>
Vector<Type> Matrix<Type>::arrange_row(const unsigned int& row_index, const Vector<unsigned int>& column_indices) const
{
    const unsigned int size = column_indices.size();

    Vector<Type> row(size);

    for(unsigned int i = 0; i < size; i++)
    {
        row[i] = data[row_index][column_indices[i]];
    }

    return(row);
}



// Vector<Type> arrange_column(const unsigned int&) const method

/// This method returns the column j of the matrix.
/// @param j Index of column.
//返回矩阵某一列
template<typename Type>
Vector<Type> Matrix<Type>::arrange_column(const unsigned int& j) const
{

    Vector<Type> column(rows_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        column[i] = data[i][j];
    }

    return(column);
}
template<typename Type>
Vector<Type> Matrix<Type>::arrange_column_range(unsigned int j,int begin,int end)const/// 获得指定列的最后dataNum个元素向量
{
     begin = begin>0 ? begin : 0;
     int dataNum = end - begin + 1;
     Vector<Type> column(dataNum);
    for(int i = begin; i <= end; i++)
    {
        column[i-begin] = data[i][j];
    }
    return(column);
}
template<typename Type>
Vector<Type> Matrix<Type>::arrange_column_last(const unsigned int& j,const int& dataNum) const
{
     return arrange_column_range(j, rows_number - dataNum, rows_number-1);
}
template<typename Type>
Vector<Type> Matrix<Type>::arrange_column(const unsigned int& j,const unsigned int& begin,const unsigned int& end) const
{
     unsigned int l = end - begin;
     Vector<Type> column(l);
    for(unsigned int i = begin; i < end; i++)
    {
        column[i-begin] = data[i][j];
    }
    return(column);
}


// Vector<Type> arrange_column(const unsigned int&) const method

/// This method returns the column j of the matrix, but only those elements specified by given indices.
/// @param column_index Index of column.
/// @param row_indices Row indices of column.
template<typename Type>
Vector<Type> Matrix<Type>::arrange_column(const unsigned int& column_index, const Vector<unsigned int>& row_indices) const
{
    const unsigned int size = row_indices.size();

    Vector<Type> column(size);

    for(unsigned int i = 0; i < size; i++)
    {
        column[i] = data[row_indices[i]][column_index];
    }

    return(column);
}


// Vector<Type> get_diagonal(void) const method

/// This method returns the diagonal of the matrix.
//取对角线元素
template<typename Type>
Vector<Type> Matrix<Type>::get_diagonal(void) const
{

    Vector<Type> diagonal(rows_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        diagonal[i] = data[i][i];
    }

    return(diagonal);
}


// void set_row(const unsigned int&, const Vector<Type>&) const method

/// This method sets new values of a single row in the matrix.
/// @param row_index Index of row.
/// @param new_row New values of single row.
template<typename Type>
void Matrix<Type>::set_row(const unsigned int& row_index, const Vector<Type>& new_row)
{
    // Set new row

    for(unsigned int i = 0; i < columns_number; i++)
    {
        data[row_index][i] = new_row[i];
    }
}


// void set_row(const unsigned int&, const Type&) method

/// This method sets a new value of a single row in the matrix.
/// @param row_index Index of row.
/// @param value New value of single row.
template<typename Type>
void Matrix<Type>::set_row(const unsigned int& row_index, const Type& value)
{
    // Set new row

    for(unsigned int i = 0; i < columns_number; i++)
    {
        data[row_index][i] = value;
    }
}


// void set_column(const unsigned int&, const Vector<Type>&) method

/// This method sets new values of a single column in the matrix.
/// @param column_index Index of column.
/// @param new_column New values of single column.
template<typename Type>
void Matrix<Type>::set_column(const unsigned int& column_index, const Vector<Type>& new_column)
{
    // Set new column

    for(unsigned int i = 0; i < rows_number; i++)
    {
        data[i][column_index] = new_column[i];
    }
}


// void set_column(const unsigned int&, const Type&) method

/// This method sets a new values of a single column in the matrix.
/// @param column_index Index of column.
/// @param value New value of single column.
template<typename Type>
void Matrix<Type>::set_column(const unsigned int& column_index, const Type& value)
{
    // Set new column
    for(unsigned int i = 0; i < rows_number; i++)
    {
        data[i][column_index] = value;
    }
}


// void set_diagonal(const Type&) method


/// This method sets a new value for the diagonal elements in the matrix.
/// The matrix must be square.
/// @param new_diagonal New value of diagonal.
template<typename Type>
void Matrix<Type>::set_diagonal(const Type& new_diagonal)
{
    // Set new column

    for(unsigned int i = 0; i < rows_number; i++)
    {
        data[i][i] = new_diagonal;
    }
}


// void set_diagonal(const Vector<Type>&) method

/// This method sets new values of the diagonal in the matrix.
/// The matrix must be square.
/// @param new_diagonal New values of diagonal.
template<typename Type>
void Matrix<Type>::set_diagonal(const Vector<Type>& new_diagonal)
{
  // Set new column

    for(unsigned int i = 0; i < rows_number; i++)
    {
        data[i][i] = new_diagonal[i];
    }
}


// void initialize_diagonal(const unsigned int&, const Type&) method

/// This method sets this matrix to be diagonal.
/// A diagonal matrix is a square matrix in which the entries outside the main diagonal are all zero.
/// It also initializes the elements on the main diagonal to a unique given value.
/// @param new_size Number of rows and colums in the matrix.
/// @param new_value Value of all the elements in the main diagonal.
template<typename Type>
void Matrix<Type>::initialize_diagonal(const unsigned int& new_size, const Type& new_value)
{
    set(new_size, new_size, 0.0);
    set_diagonal(new_value);
}


// void initialize_diagonal(const unsigned int&, const Vector<Type>&) method

/// This method sets this matrix to be diagonal.
/// A diagonal matrix is a square matrix in which the entries outside the main diagonal are all zero.
/// It also initializes the elements on the main diagonal to given values.
/// @param new_size Number of rows and colums in the matrix.
/// @param new_values Values of the elements in the main diagonal.
template<typename Type>
void Matrix<Type>::initialize_diagonal(const unsigned int& new_size, const Vector<Type>& new_values)
{
    set(new_size, new_size, 0.0);
    set_diagonal(new_values);
}


// Matrix<Type> sum_diagonal(const Type&) const method

/// This method sums a new value to the diagonal elements in the matrix.
/// The matrix must be square.
/// @param new_summing_value New summing value.
//求对角线元素和
template<typename Type>
Matrix<Type> Matrix<Type>::sum_diagonal(const Type& new_summing_value) const
{
    Matrix<Type> sum(*this);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        sum[i][i] += new_summing_value;
    }

    return(sum);
}


// Matrix<Type> sum_diagonal(const Vector<Type>&) const method

/// This method sums new values to the diagonal in the matrix.
/// The matrix must be square.
/// @param new_summing_values Vector of summing values.
template<typename Type>
Matrix<Type> Matrix<Type>::sum_diagonal(const Vector<Type>& new_summing_values) const
{
    Matrix<Type> sum(*this);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        data[i][i] += new_summing_values[i];
    }

    return(sum);
}


// void append_row(const Vector<Type>&) const method

/// This method appends a new row to the matrix.
/// The size of the row vector must be equal to the number of columns of the matrix.
/// Note that resizing is necessary here and therefore this method can be very inefficient.
/// @param new_row Row to be appended.
//添加行
template<typename Type>
void Matrix<Type>::append_row(const Vector<Type>& new_row)
{
    resize(rows_number+1, columns_number);

    set_row(rows_number-1, new_row);
}


// void append_column(const Vector<Type>&) const method

/// This method appends a new column to the matrix.
/// The size of the column vector must be equal to the number of rows of the matrix.
/// Note that resizing is necessary here and therefore this method can be very inefficient.
/// @param new_column Column to be appended.
//添加列
template<typename Type>
void Matrix<Type>::append_column(const Vector<Type>& new_column)
{
    resize(rows_number, columns_number+1);
    set_column(columns_number-1, new_column);
}


// void subtract_row(const unsigned int&) const method

/// This method removes the row with given index.
/// Note that resizing is here necessary and this method can be very inefficient.
/// @param row_index Index of row to be removed.
//移除某行
template<typename Type>
void Matrix<Type>::subtract_row(const unsigned int& row_index)
{
    Matrix<Type> new_matrix(rows_number-1, columns_number);

    for(unsigned int i = 0; i < row_index; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
          new_matrix[i][j] = data[i][j];
        }
    }

    for(unsigned int i = row_index+1; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            new_matrix[i-1][j] = data[i][j];
        }
    }

    *this = new_matrix;
}


// void subtract_column(unsigned int) method

/// This method removes the column with given index.
/// Note that resizing is here necessary and this method can be very inefficient.
/// @param column_index Index of column to be removed.
//移除某列
template<typename Type>
void Matrix<Type>::subtract_column(const unsigned int& column_index)
{
    Matrix<Type> new_matrix(rows_number, columns_number-1);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < column_index; j++)
        {
          new_matrix[i][j] = data[i][j];
        }
    }

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = column_index+1; j < columns_number; j++)
        {
            new_matrix[i][j-1] = data[i][j];
        }
    }

    *this = new_matrix;
}


// Matrix<Type> get_assembly_columns(const Matrix<Type>&) const method

/// Assemble two matrices.
/// @param other_matrix matrix to be get_assemblyd to this matrix.
template<typename Type>
Matrix<Type> Matrix<Type>::get_assembly_columns(const Matrix<Type>& other_matrix) const
{
    const unsigned int other_columns_number = other_matrix.get_columns_number();

    Matrix<Type> assembly(rows_number, columns_number + other_columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            assembly[i][j] = data[i][j];
        }
        for(unsigned int j = 0; j < other_columns_number; j++)
        {
            assembly[i][columns_number+j] = other_matrix[i][j];
        }
    }

    return(assembly);
}


// void initialize(const Type&) const method

/// This method initializes all the elements of the matrix with a given value.
/// @param value Type value.
template<typename Type>
void Matrix<Type>::initialize(const Type& value) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] = value;
        }
    }
}


// void initialize_uniform(void) const method

/// This method initializes all the elements in the matrix with random values comprised between -1 and 1.
template<typename Type>
void Matrix<Type>::initialize_uniform(void) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] = calculate_random_uniform(-1.0, 1.0);
        }
    }
}


// void initialize_uniform(const double&, const double&) const method

/// This method initializes all the elements in the matrix with random values comprised between a minimum and a maximum
/// values.
/// @param minimum Minimum possible value.
/// @param maximum Maximum possible value.
template<typename Type>
void Matrix<Type>::initialize_uniform(const double& minimum, double maximum) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] = calculate_random_uniform(minimum, maximum);
        }
    }
}


// void initialize_uniform(const Matrix<double>&, const Matrix<double>&) const method

/// This method initializes all the elements in the matrix with random values comprised between a minimum and a maximum
/// values for each element.
/// @param minimum Minimum possible values.
/// @param maximum Maximum possible values.
template<typename Type>
void Matrix<Type>::initialize_uniform(const Matrix<double>& minimum, const Matrix<double>& maximum) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] = calculate_random_uniform(minimum[i][j], maximum[i][j]);
        }
    }
}


// void initialize_normal(void) const method

/// This method assigns random values to each element in the matrix, taken from a normal distribution with
/// mean 0 and standard deviation 1.
template<typename Type>
void Matrix<Type>::initialize_normal(void) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] = calculate_random_normal(0.0, 1.0);
        }
    }
}


// void initialize_normal(const double&, const double&) const method

/// This method assigns random values to each element in the matrix, taken from a normal distribution with
/// a given mean and a given standard deviation.
/// @param mean Mean value of uniform distribution.
/// @param standard_deviation Standard deviation value of uniform distribution.
template<typename Type>
void Matrix<Type>::initialize_normal(const double& mean, double standard_deviation) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] = calculate_random_normal(mean, standard_deviation);
        }
    }
}


// void initialize_normal(const Matrix<double>&, const Matrix<double>&) const method

/// This method assigns random values to each element in the vector, taken from normal distributions with
/// given means and standard deviations for each element.
/// @param mean Mean values of uniform distributions.
/// @param standard_deviation Standard deviation values of uniform distributions.
template<typename Type>
void Matrix<Type>::initialize_normal(const Matrix<double>& mean, const Matrix<double>& standard_deviation) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] = calculate_random_uniform(mean[i][j], standard_deviation[i][j]);
        }
    }
}


// void initialize_identity(void) const method

/// This method sets the diagonal elements in the matrix with ones and the rest elements with zeros. The matrix
/// must be square.
template<typename Type>
void Matrix<Type>::initialize_identity(void) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(i==j)
            {
                data[i][j] = 1;
            }
            else
            {
                data[i][j] = 0;
            }
        }
    }
}


// void initialize_diagonal(const Type&) const method

/// This method sets the diagonal elements in the matrix with ones and the rest elements with a given value.
/// The matrix must be square.
template<typename Type>
void Matrix<Type>::initialize_diagonal(const Type& value) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(i==j)
            {
                data[i][j] = value;
            }
            else
            {
                data[i][j] = 0;
            }
        }
    }
}


// double calculate_trace(void) const method

/// This method returns the trace of the matrix, which is defined to be the sum of the main diagonal elements.
/// The matrix must be square.
//计算矩阵的迹
template<typename Type>
double Matrix<Type>::calculate_trace(void) const
{
    double trace = 0.0;

    for(unsigned int i = 0; i < rows_number; i++)
    {
        trace += data[i][i];
    }

    return(trace);
}


// Vector<double> calculate_mean(void) const method

/// This method returns a vector with the mean values of all the matrix columns.
/// The size is equal to the number of columns in the matrix.
//返回每列的均值
template<typename Type>
Vector<double> Matrix<Type>::calculate_mean(void) const
{
    // Mean
    Vector<double> mean(columns_number, 0.0);

    for(unsigned int j = 0; j < columns_number; j++)
    {
        mean[j] = 0.0;

        for(unsigned int i = 0; i < rows_number; i++)
        {
            mean[j] += data[i][j];
        }

        mean[j] /= (double)rows_number;
    }

    return(mean);
}


// Vector<double> calculate_mean(const Vector<unsigned int>&) const method

/// This method returns a vector with the mean values of given columns.
/// The size of the vector is equal to the size of the column indices vector.
/// @param column_indices Indices of columns.
template<typename Type>
Vector<double> Matrix<Type>::calculate_mean(const Vector<unsigned int>& column_indices) const
{
    const unsigned int column_indices_size = column_indices.size();

    unsigned int column_index;

    // Mean

    Vector<double> mean(column_indices_size, 0.0);

    for(unsigned int j = 0; j < column_indices_size; j++)
    {
        column_index = column_indices[j];

        mean[j] = 0.0;

        for(unsigned int i = 0; i < rows_number; i++)
        {
            mean[j] += data[i][column_index];
        }

        mean[j] /= (double)rows_number;
    }

    return(mean);
}


// Vector<double> calculate_mean(const Vector<unsigned int>&, const Vector<unsigned int>&) const method

/// This method returns a vector with the mean values of given columns for given rows.
/// The size of the vector is equal to the size of the column indices vector.
/// @param row_indices Indices of rows.
/// @param column_indices Indices of columns.
template<typename Type>
Vector<double> Matrix<Type>::calculate_mean(const Vector<unsigned int>& row_indices, const Vector<unsigned int>& column_indices) const
{
    const unsigned int row_indices_size = row_indices.size();
    const unsigned int column_indices_size = column_indices.size();
    unsigned int row_index;
    unsigned int column_index;

    // Mean

    Vector<double> mean(column_indices_size, 0.0);

    for(unsigned int j = 0; j < column_indices_size; j++)
    {
        column_index = column_indices[j];

        mean[j] = 0.0;

        for(unsigned int i = 0; i < row_indices_size; i++)
        {
            row_index = row_indices[i];

            mean[j] += data[row_index][column_index];
        }

        mean[j] /= (double)rows_number;
    }

    return(mean);
}


// Vector<double> calculate_mean_standard_deviation(void) const method

/// This method returns a vector of vectors with the mean and standard deviation values of all the matrix columns.
/// The size of the vector is two.
/// The size of each element is equal to the number of columns in the matrix.
template<typename Type>
Vector< Vector<double> > Matrix<Type>::calculate_mean_standard_deviation(void) const
{
    // Mean

    Vector<double> mean(columns_number, 0.0);

    for(unsigned int j = 0; j < columns_number; j++)
    {
        mean[j] = 0.0;

        for(unsigned int i = 0; i < rows_number; i++)
        {
            mean[j] += data[i][j];
        }

        mean[j] /= (double)rows_number;
    }

    // Standard deviation

    Vector<double> standard_deviation(columns_number, 0.0);

    for(unsigned int j = 0; j < columns_number; j++)
    {
        standard_deviation[j] = 0.0;

        for(unsigned int i = 0; i < rows_number; i++)
        {
            standard_deviation[j] += (data[i][j] - mean[j])*(data[i][j] - mean[j]);
        }

        standard_deviation[j] = sqrt(standard_deviation[j]/(rows_number-1.0));
    }

    // Mean and standard deviation of data

    Vector< Vector<double> > mean_standard_deviation(2);

    mean_standard_deviation[0] = mean;
    mean_standard_deviation[1] = standard_deviation;

    return(mean_standard_deviation);
}


// Vector<double> calculate_mean_standard_deviation(const Vector<unsigned int>&) const method

/// This method returns a vector of vectors with the mean and standard deviation values of given columns.
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector.
/// @param column_indices Indices of columns.
template<typename Type>
Vector< Vector<double> > Matrix<Type>::calculate_mean_standard_deviation(const Vector<unsigned int>& column_indices) const
{
    const unsigned int column_indices_size = column_indices.size();

    unsigned int column_index;

    // Mean

    Vector<double> mean(column_indices_size, 0.0);

    for(unsigned int j = 0; j < column_indices_size; j++)
    {
        column_index = column_indices[j];

        mean[j] = 0.0;

        for(unsigned int i = 0; i < rows_number; i++)
        {
            mean[j] += data[i][column_index];
        }

        mean[j] /= (double)rows_number;
    }

    // Standard deviation

    Vector<double> standard_deviation(column_indices_size, 0.0);

    for(unsigned int j = 0; j < column_indices_size; j++)
    {
        column_index = column_indices[j];

        standard_deviation[j] = 0.0;

        for(unsigned int i = 0; i < rows_number; i++)
        {
            standard_deviation[j] += (data[i][column_index] - mean[j])*(data[i][column_index] - mean[j]);
        }

        standard_deviation[j] = sqrt(standard_deviation[j]/(rows_number-1.0));
    }

    // Mean and standard deviation

    Vector< Vector<double> > mean_standard_deviation(2);

    mean_standard_deviation[0] = mean;
    mean_standard_deviation[1] = standard_deviation;

    return(mean_standard_deviation);
}


// Vector<double> calculate_mean_standard_deviation(const Vector<unsigned int>&, const Vector<unsigned int>&) const method

/// This method returns a vector of vectors with the mean and standard deviation values of given columns for given rows.
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector.
/// @param row_indices Indices of rows.
/// @param column_indices Indices of columns.
template<typename Type>
Vector< Vector<double> > Matrix<Type>::calculate_mean_standard_deviation(const Vector<unsigned int>& row_indices, const Vector<unsigned int>& column_indices) const
{
    const unsigned int row_indices_size = row_indices.size();
    const unsigned int column_indices_size = column_indices.size();
    unsigned int row_index;
    unsigned int column_index;

    // Mean

    Vector<double> mean(column_indices_size, 0.0);

    for(unsigned int j = 0; j < column_indices_size; j++)
    {
        column_index = column_indices[j];

        mean[j] = 0.0;

        for(unsigned int i = 0; i < row_indices_size; i++)
        {
            row_index = row_indices[i];

            mean[j] += data[row_index][column_index];
        }

        mean[j] /= (double)rows_number;
    }

    // Standard deviation

    Vector<double> standard_deviation(column_indices_size, 0.0);

    for(unsigned int j = 0; j < column_indices_size; j++)
    {
        column_index = column_indices[j];

        standard_deviation[j] = 0.0;

        for(unsigned int i = 0; i < row_indices_size; i++)
        {
            row_index = row_indices[i];

            standard_deviation[j] += (data[row_index][column_index] - mean[j])*(data[row_index][column_index] - mean[j]);
        }

        standard_deviation[j] = sqrt(standard_deviation[j]/(rows_number-1.0));
    }

    // Mean and standard deviation

    Vector< Vector<double> > mean_standard_deviation(2);

    mean_standard_deviation[0] = mean;
    mean_standard_deviation[1] = standard_deviation;

    return(mean_standard_deviation);
}


// Vector< Vector<Type> > calculate_minimum_maximum(void) const method

/// This method returns a vector of vectors with the minimum and maximum values of all the matrix columns.
/// The size of the vector is two.
/// The size of each element is equal to the number of columns in the matrix.
//返回每列的最大最小值
template<typename Type>
Vector< Vector<Type> > Matrix<Type>::calculate_minimum_maximum(void) const
{
    Vector< Vector<Type> > minimum_maximum(2);

    Vector<Type> minimum(columns_number,  1.0e99);
    Vector<Type> maximum(columns_number, -1.0e99);

    for(unsigned int j = 0; j < columns_number; j++)
    {
        for(unsigned int i = 0; i < rows_number; i++)
        {
            if(data[i][j] < minimum[j])
            {
                minimum[j] = data[i][j];
            }

            if(data[i][j] > maximum[j])
            {
                maximum[j] = data[i][j];
            }
        }
    }

    // Minimum and maximum

    minimum_maximum[0] = minimum;
    minimum_maximum[1] = maximum;

    return(minimum_maximum);
}


// Vector<double> calculate_minimum_maximum(const Vector<unsigned int>&) const method

/// This method returns a vector of vectors with the minimum and maximum values of given columns.
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector.
/// @param column_indices Indices of columns.
template<typename Type>
Vector< Vector<Type> > Matrix<Type>::calculate_minimum_maximum(const Vector<unsigned int>& column_indices) const
{
    const unsigned int column_indices_size = column_indices.size();
    unsigned int column_index;

    Vector<Type> minimum(column_indices_size,  1.0e99);
    Vector<Type> maximum(column_indices_size, -1.0e99);

    for(unsigned int j = 0; j < column_indices_size; j++)
    {
        column_index = column_indices[j];

        for(unsigned int i = 0; i < rows_number; i++)
        {
            if(data[i][column_index] < minimum[j])
            {
                minimum[j] = data[i][column_index];
            }

            if(data[i][column_index] > maximum[j])
            {
                maximum[j] = data[i][column_index];
            }
        }
    }

    // Minimum and maximum

    Vector< Vector<Type> > minimum_maximum(2);

    minimum_maximum[0] = minimum;
    minimum_maximum[1] = maximum;

    return(minimum_maximum);
}


// Vector<double> calculate_minimum_maximum(const Vector<unsigned int>&, const Vector<unsigned int>&) const method

/// This method returns a vector of vectors with the minimum and maximum values of given columns for given rows.
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector.
/// @param row_indices Indices of rows.
/// @param column_indices Indices of columns.
template<typename Type>
Vector< Vector<Type> > Matrix<Type>::calculate_minimum_maximum(const Vector<unsigned int>& row_indices, const Vector<unsigned int>& column_indices) const
{
    const unsigned int row_indices_size = row_indices.size();
    const unsigned int column_indices_size = column_indices.size();

    Vector<Type> minimum(column_indices_size,  1.0e99);
    Vector<Type> maximum(column_indices_size, -1.0e99);

    unsigned int row_index;
    unsigned int column_index;

    for(unsigned int j = 0; j < column_indices_size; j++)
    {
        column_index = column_indices[j];

        for(unsigned int i = 0; i < row_indices_size; i++)
        {
            row_index = row_indices[i];

            if(data[row_index][column_index] < minimum[j])
            {
                minimum[j] = data[row_index][column_index];
            }

            if(data[row_index][column_index] > maximum[j])
            {
                maximum[j] = data[row_index][column_index];
            }
        }
    }

    // Minimum and maximum

    Vector< Vector<Type> > minimum_maximum(2);

    minimum_maximum[0] = minimum;
    minimum_maximum[1] = maximum;

    return(minimum_maximum);
}


// Vector<double> calculate_statistics(void) const method

/// This method returns the basic statistics of the columns.
/// The format is a vector of size four.
/// The first subvector contains the minimum values of the columns.
/// The second subvector contains the maximum values of the columns.
/// The third subvector contains the mean values of the columns.
/// The fourth subvector contains the standard deviation values of the columns.
//计算矩阵的统计数据
template<typename Type>
Vector< Vector<double> > Matrix<Type>::calculate_statistics(void) const
{
    const Vector< Vector<double> > minimum_maximum = calculate_minimum_maximum();
    const Vector< Vector<double> > mean_standard_deviation = calculate_mean_standard_deviation();

    return(minimum_maximum.get_assembly(mean_standard_deviation));
}


// Vector< Vector< Vector<Type> > > calculate_histogram(const unsigned int&) const method

/// This method calculates a histogram for each column, each having a given number of bins.
/// It returns a vector of vectors of vectors.
/// The size of the main vector is the number of columns.
/// Each subvector contains the frequencies and centers of that colums.
/// @param bins_number Number of bins for each histogram.
template<typename Type>
Vector< Vector< Vector<Type> > > Matrix<Type>::calculate_histogram(const unsigned int& bins_number) const
{
    Vector< Vector< Vector<Type> > > histogram(columns_number);

    Vector<Type> column(rows_number);

    for(unsigned int i = 0; i < columns_number; i++)
    {
        column = arrange_column(i);

        histogram[i] = column.calculate_histogram(bins_number);
    }

    return(histogram);
}
template<typename Type>
Vector< Vector< Vector<Type> > > Matrix<Type>::calculate_histogram(void) const
{
    Vector< Vector< Vector<Type> > > histogram(columns_number);

    Vector<Type> column(rows_number);

    for(unsigned int i = 0; i < columns_number; i++)
    {
        column = arrange_column(i);

        histogram[i] = column.calculate_histogram();
    }

    return(histogram);
}
template<typename Type>
void Matrix<Type>::scale_mean_standard_deviation_self(){
  // Mean Deviation
    Vector<double> mean(columns_number, 0.0);
    Vector<double> standard_deviation(columns_number, 0.0);
    for(unsigned int j = 0; j < columns_number; j++)
    {
        mean[j] = 0.0;
        standard_deviation[j] = 0.0;
        for(unsigned int i = 0; i < rows_number; i++)
        {
            mean[j] += data[i][j];
            standard_deviation[j] += (data[i][j] - mean[j])*(data[i][j] - mean[j]);
        }
        mean[j] /= (double)rows_number;
        standard_deviation[j] = sqrt(standard_deviation[j]/(rows_number-1.0));
    }


    // Rescale data

    for(unsigned int j = 0; j < columns_number; j++)
    {
        if(standard_deviation[j] < 1e-99)
        {
            std::cout << "Those values won't be scaled.\n";
            // Do nothing
        }
        else
        {
            for(unsigned int i = 0; i < rows_number; i++)
            {
                data[i][j] = (data[i][j] - mean[j])/standard_deviation[j];
            }
        }
    }
}
template<typename Type>
void Matrix<Type>::scale_mean_standard_deviation(const Vector<double>& mean, const Vector<double>& standard_deviation) const
{
    // Rescale data

    for(unsigned int j = 0; j < columns_number; j++)
    {
        if(standard_deviation[j] < 1e-99)
        {
            std::cout << "Those values won't be scaled.\n";
            // Do nothing
        }
        else
        {
            for(unsigned int i = 0; i < rows_number; i++)
            {
                data[i][j] = (data[i][j] - mean[j])/standard_deviation[j];
            }
        }
    }
}
template<typename Type>
void Matrix<Type>::scale_minimum_maximum_self()  //自己根据每列的最大最小值进行缩放
{
    Vector<Type> minimum(columns_number,  1.0e99);
    Vector<Type> maximum(columns_number, -1.0e99);

    for(unsigned int j = 0; j < columns_number; j++)
    {
        for(unsigned int i = 0; i < rows_number; i++)
        {
            if(data[i][j] < minimum[j])
            {
                minimum[j] = data[i][j];
            }

            if(data[i][j] > maximum[j])
            {
                maximum[j] = data[i][j];
            }
        }
    }

    // Rescale data

    for(unsigned int j = 0; j < columns_number; j++)
    {
        if(maximum[j] - minimum[j] < 1e-99)
        {
            std::cout << "Those values won't be scaled.\n";

            // Do nothing
        }
        else
        {
            for(unsigned int i = 0; i < rows_number; i++)
            {
                data[i][j] = 2.0*(data[i][j] - minimum[j])/(maximum[j]-minimum[j])-1.0;
            }
        }
    }
}
template<typename Type>
void Matrix<Type>::scale_minimum_maximum(const Vector<double>& minimum, const Vector<double>& maximum) const
{
    // Rescale data

    for(unsigned int j = 0; j < columns_number; j++)
    {
        if(maximum[j] - minimum[j] < 1e-99)
        {
            std::cout << "Those values won't be scaled.\n";

            // Do nothing
        }
        else
        {
            for(unsigned int i = 0; i < rows_number; i++)
            {
                data[i][j] = 2.0*(data[i][j] - minimum[j])/(maximum[j]-minimum[j])-1.0;
            }
        }
    }
}
template<typename Type>
void Matrix<Type>::unscale_mean_standard_deviation(const Vector<double>& mean, const Vector<double>& standard_deviation) const
{
    for(unsigned int j = 0; j < columns_number; j++)
    {
        if(standard_deviation[j] < 1e-99)
        {
            std::cout << "Those columns won't be scaled.\n";
          // Do nothing
        }
        else
        {
            for(unsigned int i = 0; i < rows_number; i++)
            {
                data[i][j] = data[i][j]*standard_deviation[j] + mean[j];
            }
        }
    }
}
template<typename Type>
void Matrix<Type>::unscale_minimum_maximum(const Vector<double>& minimum, const Vector<double>& maximum) const
{
    for(unsigned int j = 0; j < columns_number; j++)
    {
        if(maximum[j] - minimum[j] < 1e-99)
        {
            // Do nothing
        }
        else
        {
            for(unsigned int i = 0; i < rows_number; i++)
            {
                data[i][j] = 0.5*(data[i][j] + 1.0)*(maximum[j]-minimum[j]) + minimum[j];
            }
        }
    }
}
template<typename Type>
Vector<unsigned int> Matrix<Type>::calculate_minimal_indices(void) const
{
    Type minimum = data[0][0];
    Vector<unsigned int> minimal_indices(2, 0);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] < minimum)
            {
                minimum = data[i][j];
                minimal_indices[0] = i;
                minimal_indices[1] = j;
            }
        }
    }

    return(minimal_indices);
}
template<typename Type>
Vector<unsigned int> Matrix<Type>::calculate_maximal_indices(void) const
{
    Type maximum = data[0][0];

    Vector<unsigned int> maximal_indices(2, 0);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] > maximum)
            {
                maximum = data[i][j];
                maximal_indices[0] = i;
                maximal_indices[1] = j;
            }
        }
    }

    return(maximal_indices);
}
template<typename Type>
Vector< Vector<unsigned int> > Matrix<Type>::calculate_minimal_maximal_indices(void) const
{
    Type minimum = data[0][0];
    Type maximum = data[0][0];

    Vector<unsigned int> minimal_indices(2, 0);
    Vector<unsigned int> maximal_indices(2, 0);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] < minimum)
            {
                minimum = data[i][j];
                minimal_indices[0] = i;
                minimal_indices[1] = j;
            }

            if(data[i][j] > maximum)
            {
                maximum = data[i][j];
                maximal_indices[0] = i;
                maximal_indices[1] = j;
            }
        }
    }

    Vector< Vector<unsigned int> > minimal_maximal_indices(2);
    minimal_maximal_indices[0] = minimal_indices;
    minimal_maximal_indices[1] = maximal_indices;

    return(minimal_maximal_indices);
}
template<typename Type>
double Matrix<Type>::calculate_sum_squared_error(const Matrix<double>& other_matrix) const
{
    double sum_squared_error = 0.0;

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            sum_squared_error += (data[i][j] - other_matrix[i][j])*(data[i][j] - other_matrix[i][j]);
        }
    }

    return(sum_squared_error);
}
template<typename Type>
double Matrix<Type>::calculate_sum_squared_error(const Vector<double>& vector) const
{
    double sum_squared_error = 0.0;

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            sum_squared_error += (data[i][j] - vector[j])*(data[i][j] - vector[j]);
        }
    }

    return(sum_squared_error);
}
template<typename Type>
Vector<double> Matrix<Type>::calculate_rows_norm(void) const
{
    Vector<Type> rows_norm(rows_number, 0.0);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            rows_norm[i] += data[i][j]*data[i][j];
        }

        rows_norm[i] = sqrt(rows_norm[i]);
    }

    return(rows_norm);
}
template<typename Type>
Matrix<Type> Matrix<Type>::calculate_absolute_value(void) const
{
    Matrix<Type> absolute_value(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] > 0)
            {
                absolute_value[i][j] = data[i][j];
            }
            else
            {
                absolute_value[i][j] = -data[i][j];
            }
        }
    }

    return(absolute_value);
}
template<typename Type>
Matrix<Type> Matrix<Type>::calculate_transpose(void) const
{
    Matrix<Type> transpose(columns_number, rows_number);

    for(unsigned int i = 0; i < columns_number; i++)
    {
        for(unsigned int j = 0; j < rows_number; j++)
        {
            transpose[i][j] = data[j][i];
        }
    }

    return(transpose);
}
template<typename Type>
Type Matrix<Type>::calculate_determinant(void) const
{
    Type determinant = 0;

    if(rows_number == 0)
    {
    }
    else if(rows_number == 1)
    {
        determinant = data[0][0];
    }
    else if(rows_number == 2)
    {
        determinant = data[0][0]*data[1][1] - data[1][0]*data[0][1];
    }
    else
    {
 //      int sign;
        //按第一行展开??
        for(unsigned int column_index = 0; column_index < columns_number; column_index++)
        {
            // Calculate sub data

            Matrix<Type> sub_matrix(rows_number-1, columns_number-1);

            for(unsigned int i = 1; i < rows_number; i++) //第一行永远也不会有
            {
                unsigned int j2 = 0;

                for(unsigned int j = 0; j < columns_number; j++)
                {
                    if(j == column_index)
                    {
                        continue;
                    }

                    sub_matrix[i-1][j2] = data[i][j];

                    j2++;
                }
            }

            determinant += pow(-1.0, column_index+2.0)*data[0][column_index]*sub_matrix.calculate_determinant();
        }
    }

    return(determinant);
}
template<typename Type>
Matrix<Type> Matrix<Type>::calculate_cofactor(void) const
{
    Matrix<double> cofactor(rows_number, columns_number);

    Matrix<double> c(rows_number-1, columns_number-1);

    for(unsigned int j = 0; j < rows_number; j++)
    {
        for(unsigned int i = 0; i < rows_number; i++)
        {
            // Form the adjoint a[i][j]

            unsigned int i1 = 0;

            for(unsigned int ii = 0; ii < rows_number; ii++)
            {
                if(ii == i)
                {
                    continue;
                }

                unsigned int j1 = 0;

                for(unsigned int jj = 0; jj < rows_number; jj++)
                {
                    if(jj == j)
                    {
                        continue;
                    }

                    c[i1][j1] = data[ii][jj];
                    j1++;
                }
                i1++;
            }

            double determinant = c.calculate_determinant();

            cofactor[i][j] = pow(-1.0, i+j+2.0)*determinant;
        }
    }

    return(cofactor);
}
template<typename Type>
Matrix<Type> Matrix<Type>::calculate_inverse(void) const
{
    const double determinant = calculate_determinant();

    if(determinant == 0.0)
    {
    }

    // Calculate cofactor matrix
    const Matrix<double> cofactor = calculate_cofactor();

    // Adjoint matrix is the transpose of cofactor matrix

    const Matrix<double> adjoint = cofactor.calculate_transpose();

    // Inverse matrix is adjoint matrix divided by matrix determinant

    const Matrix<double> inverse = adjoint/determinant;

    return(inverse);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator + (const Type& scalar) const
{
    Matrix<Type> sum(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            sum[i][j] = data[i][j] + scalar;
        }
    }

    return(sum);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator + (const Vector<Type>& vector) const
{

    Matrix<Type> sum(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            sum[i][j] = data[i][j] + vector[i];
        }
    }

    return(sum);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator + (const Matrix<Type>& other_matrix) const
{
    Matrix<Type> sum(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            sum[i][j] = data[i][j] + other_matrix[i][j];
        }
    }

    return(sum);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator - (const Type& scalar) const
{
    Matrix<Type> difference(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            difference[i][j] = data[i][j] - scalar;
        }
    }

    return(difference);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator - (const Vector<Type>& vector) const
{
    Matrix<Type> difference(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            difference[i][j] = data[i][j] - vector[i];
        }
    }

    return(difference);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator - (const Matrix<Type>& other_matrix) const
{
    Matrix<Type> difference(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            difference[i][j] = data[i][j] - other_matrix[i][j];
        }
    }

    return(difference);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator * (const Type& scalar) const
{
    Matrix<Type> product(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
             product[i][j] = data[i][j]*scalar;
        }
    }

    return(product);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator * (const Vector<Type>& vector) const
{
    Matrix<Type> product(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            product[i][j] = data[i][j]*vector[i];
        }
    }

    return(product);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator * (const Matrix<Type>& other_matrix) const
{
    Matrix<Type> product(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            product[i][j] = data[i][j]*other_matrix[i][j];
        }
    }

    return(product);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator / (const Type& scalar) const
{
    Matrix<Type> cocient(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            cocient[i][j] = data[i][j]/scalar;
        }
    }

    return(cocient);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator / (const Vector<Type>& vector) const
{
    Matrix<Type> cocient(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            cocient[i][j] = data[i][j]/vector[j];
        }
    }

    return(cocient);
}
template<typename Type>
inline Matrix<Type> Matrix<Type>::operator / (const Matrix<Type>& other_matrix) const
{
    Matrix<Type> cocient(rows_number, columns_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            cocient[i][j] = data[i][j]/other_matrix[i][j];
        }
    }

    return(cocient);
}
template<typename Type>
inline void Matrix<Type>::operator += (const Type& value)
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] += value;
        }
    }
}
template<typename Type>
inline void Matrix<Type>::operator += (const Matrix<Type>& other_matrix)
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] += other_matrix[i][j];
        }
    }
}
template<typename Type>
inline void Matrix<Type>::operator -= (const Type& value)
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] -= value;
        }
    }
}
template<typename Type>
inline void Matrix<Type>::operator -= (const Matrix<Type>& other_matrix)
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] -= other_matrix[i][j];
        }
    }
}
template<typename Type>
inline void Matrix<Type>::operator *= (const Type& value)
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] *= value;
        }
    }
}
template<typename Type>
inline void Matrix<Type>::operator *= (const Matrix<Type>& other_matrix)
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] *= other_matrix[i][j];
        }
    }
}
template<typename Type>
inline void Matrix<Type>::operator /= (const Type& value)
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] /= value;
        }
    }
}
template<typename Type>
inline void Matrix<Type>::operator /= (const Matrix<Type>& other_matrix)
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            data[i][j] /= other_matrix[i][j];
        }
    }
}
template<typename Type>
Vector<Type> Matrix<Type>::dot(const Vector<Type>& vector) const
{
    // Calculate matrix-vector poduct

    Vector<Type> product(rows_number);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        product[i] = 0;

        for(unsigned int j = 0; j < columns_number; j++)
        {
            product[i] += vector[j]*data[i][j];
        }
    }

    return(product);
}
template<typename Type>
Matrix<Type> Matrix<Type>::dot(const Matrix<Type>& other_matrix) const
{
    unsigned int other_columns_number = other_matrix.get_columns_number();

    Matrix<Type> product(rows_number, other_columns_number, 0.0);

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < other_columns_number; j++)
        {
            for(unsigned int k = 0; k < columns_number; k++)
            {
                 product[i][j] += data[i][k]*other_matrix[k][j];
            }
        }
    }

    return(product);
}
template<typename Type>
Matrix<Type> Matrix<Type>::direct(const Matrix<Type>& other_matrix) const
{
    const unsigned int other_rows_number = other_matrix.get_rows_number();
    const unsigned int other_columns_number = other_matrix.get_columns_number();

    const Matrix<Type> direct(rows_number*other_rows_number, columns_number*other_columns_number);

    return(direct);
}
template<typename Type>
bool Matrix<Type>::empty(void) const
{
    if(rows_number == 0 && columns_number == 0)
    {
        return(true);
    }
    else
    {
        return(false);
    }

}
template<typename Type>
bool Matrix<Type>::is_square(void) const
{
    if(rows_number == columns_number)
    {
        return(true);
    }
    else
    {
        return(false);
    }

}
template<typename Type>
bool Matrix<Type>::is_symmetric(void) const
{
    const Matrix<Type> transpose = calculate_transpose();

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(data[i][j] != transpose[i][j])
            {
                return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
bool Matrix<Type>::is_antisymmetric(void) const
{
    const Matrix<Type> transpose = calculate_transpose();

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(i != j && -data[i][j] != transpose[i][j])
            {
                return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
bool Matrix<Type>::is_diagonal(void) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(i != j && data[i][j] != 0)
            {
                return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
bool Matrix<Type>::is_scalar(void) const
{
    // To do
    return(false);
}
template<typename Type>
bool Matrix<Type>::is_identity(void) const
{
    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            if(i != j && data[i][j] != 0)
            {
                return(false);
            }
            else if(i == j && data[i][j] != 1)
            {
                return(false);
            }
        }
    }

    return(true);
}
template<typename Type>
void Matrix<Type>::print(void) const
{
    std::cout << *this;
}
template<typename Type>
void Matrix<Type>::load(const std::string& filename)
{
    std::ifstream file(filename.c_str());

    if(!file.is_open())
    {
        std::ostringstream buffer;
        buffer << "no file";
        throw std::logic_error(buffer.str());
    }

    // Set matrix sizes

    std::string line;

    std::getline(file, line);

    if(line.empty())
    {
        set();
    }
    else
    {
        std::istringstream buffer(line);

        std::istream_iterator<std::string> it(buffer);
        std::istream_iterator<std::string> end;

        const std::vector<std::string> results(it, end);

        const unsigned int new_columns_number = results.size();

        unsigned int new_rows_number = 1;

        while(file.good())
        {
            getline(file, line);

            if(!line.empty())
            {
                new_rows_number++;
            }
        }

        set(new_rows_number, new_columns_number);

        // Clear file

        file.clear();
        file.seekg(0, std::ios::beg);

        for(unsigned int i = 0; i < rows_number; i++)
        {
            for(unsigned int j = 0; j < columns_number; j++)
            {
                file >> data[i][j];
            }
        }
    }

    // Close file

    file.close();
}
template<typename Type>
void Matrix<Type>::save(const std::string& filename) const
{
    std::ofstream file(filename.c_str());

    if(!file.is_open())
    {
        std::ostringstream buffer;
        buffer << "no file" << std::endl;
        throw std::logic_error(buffer.str());
    }

    // Write file

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            file << data[i][j] << " ";
        }

        file << std::endl;
    }

    // Close file

    file.close();
}
template<typename Type>
std::string Matrix<Type>::to_string(void) const
{
    std::ostringstream buffer;

    buffer << *this;

    return(buffer.str());
}
template<typename Type>
Matrix<std::string> Matrix<Type>::get_string_matrix(void) const
{
    Matrix<std::string> string_matrix(rows_number, columns_number);

    std::ostringstream buffer;

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            buffer.str("");
            buffer << (*this)[i][j];

            string_matrix[i] = buffer.str();
        }
    }

    return(string_matrix);
}
template<typename Type>
Vector<Type> Matrix<Type>::to_vector(void) const
{
    Vector<Type> vector(rows_number*columns_number);

    unsigned int index = 0;

    for(unsigned int i = 0; i < rows_number; i++)
    {
        for(unsigned int j = 0; j < columns_number; j++)
        {
            vector[index] = data[i][j];
            index++;
        }
    }

    return(vector);
}

template<typename Type>
double Matrix<Type>::calculate_random_uniform(const double& minimum, double maximum) const
{
    const double random = (double)rand()/(RAND_MAX+1.0);

    const double random_uniform = minimum + (maximum-minimum)*random;

    return(random_uniform);
}


template<typename Type>
double Matrix<Type>::calculate_random_normal(const double& mean, double standard_deviation) const
{
    double random_uniform_1;

    do
    {
        random_uniform_1 = (double)rand()/(RAND_MAX+1.0);

    }while(random_uniform_1 == 0.0);

    const double random_uniform_2 = (double)rand()/(RAND_MAX+1.0);

    // Box-Muller transformation

    const double pi = 4.0*atan(1.0);

    const double random_normal = mean + sqrt(-2.0*log(random_uniform_1))*sin(2.0*pi*random_uniform_2)*standard_deviation;

    return(random_normal);
}
#endif
