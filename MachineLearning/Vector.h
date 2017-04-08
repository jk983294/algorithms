#ifndef __VECTOR_H__
#define __VECTOR_H__

// System includes

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>

#include <fstream>
#include <iostream>
#include <iterator>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/// Forward declaration of Matrix template
template<class Type> class Matrix;

template <class Type>
class Vector : public std::vector<Type>
{
public:
    explicit Vector(void);
    explicit Vector(const unsigned int& new_size) ;
    explicit Vector(const unsigned int& new_size, const Type& value);
    explicit Vector(const std::string& filename);
    // 步长序列构造函数Sequential constructor.
    explicit Vector(const Type& first, const int& step, const Type& last);
    template<class InputIterator>   /// Input iterators constructor
    Vector(InputIterator first, InputIterator last);
    Vector(const Vector<Type>& other_vector);

    ~Vector(void);

    inline bool operator == (const Type& value) const;
    inline bool operator != (const Type& value) const;
    inline bool operator > (const Type& value) const;
    inline bool operator < (const Type& value) const;
    inline bool operator >= (const Type& value) const;
    inline bool operator <= (const Type& value) const;

// Set METHODS
    void set(void);     //长度设为0
    void set(const unsigned int& new_size);
    void set(const unsigned int& new_size, const Type& new_value);
    void set(const std::string& filename);
    void set(const Type& first, const int& step, const Type& last); //设置步长序列
    void set(const Type& first, const double& step, const Type& last);
    void set(const Vector& other_vector);


//initialize method
    void initialize(const Type& value);
    void initialize_sequential(void);   //设置步长序列,步长为1，长度为size()
    void initialize_uniform(void);  //初始化为[-1,1]的均匀分布随机值
    void initialize_uniform(const double& minimum, double maximum);//初始化为[minimum,maximum]的均匀分布随机值
    void initialize_uniform(const Vector<double>& minimum, const Vector<double>& maximum);
    void initialize_normal(void);   //初始化为均值为0，方差为1的正态分布随机值
    void initialize_normal(const double& mean, double standard_deviation);
    void initialize_normal(const Vector<double>& mean, const Vector<double>& standard_deviation);

///calculate method
    //根据给定均值方差来缩放数据
    void scale_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation);
    Vector<Type> calculate_scaled_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation) const;
    Vector<Type> calculate_unscaled_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation) const;
    void unscale_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation);
    //根据给定最大最小值来缩放数据
    void scale_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum);
    Vector<Type> calculate_scaled_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum) const;
    Vector<Type> calculate_unscaled_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum) const;
    void unscale_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum);
    //自身进行缩放，找到自己向量中的最大最小值进行缩放
    void scale_self_minimum_maximum(void);
    Type calculate_minimum(void) const; //返回序列中的最小值
    Type calculate_maximum(void) const;
    Vector<Type> calculate_minimum_maximum(void) const;//返回向量的最大最小值
    unsigned int calculate_minimal_index(void) const;   //最小元素下标
    unsigned int calculate_maximal_index(void) const;
    Vector<unsigned int> calculate_minimal_maximal_index(void) const;
    //只能用于递增向量，返回向量中第一个大于给定value的元素下标
    unsigned int calculate_cumulative_index(const Type& value) const;
    //返回与给定value最接近元素下标
    unsigned int calculate_closest_index(const Type& value) const;
    //向量的元素都幂次运算
    Vector<Type> calculate_pow(const Type& exponent) const;
    //竞争向量，原向量最大元素变为1，其余全部为0
    Vector<Type> calculate_competitive(void) const;
    //softmax向量，该向量和为1，每个元素被解释成概率
    Vector<Type> calculate_softmax(void) const;
    // softmax Jacobian of this vector
    Matrix<Type> calculate_softmax_Jacobian(void) const;
    //生成二进制bool向量，vaule>=0.5则为true，否则为false
    Vector<bool> calculate_binary(void) const;
    Type calculate_sum(void) const;         //向量元素和
    Type calculate_product(void) const;    //向量元素积
    double calculate_mean(void) const;     //向量元素的均值
    double calculate_standard_deviation(void) const;//向量元素的标准差 sqrt(sigma(power(xi-mean))/n)
    Vector<double> calculate_mean_standard_deviation(void) const;
    Vector<double> calculate_statistics(void) const;    //统计值，包括最大最小值，均值方差
    double calculate_norm(void) const;  //计算向量的模  sqrt(sigma(xi*xi))

///计算与其他向量、矩阵之间的运算
    // 计算两个向量之间的距离  sqrt(sigma((x1[i]-x2[i])*x1[i]-x2[i]))
    double calculate_distance(const Vector<double>& other_vector) const;
    // 计算和另一个向量的误差平方和
    double calculate_sum_squared_error(const Vector<double>& other_vector) const;
    //计算和另一个向量的Minkowski误差sigma(pow((x1[i]-x2[i]), Minkowski_parameter))
    double calculate_Minkowski_error(const Vector<double>& other_vector, double Minkowski_parameter) const;
    //矩阵i行元素扩大vector[i]倍
    inline Matrix<Type> operator * (const Matrix<Type>& matrix) const;
    //向量 * 矩阵 = 向量
    Vector<Type> dot(const Matrix<Type>& matrix) const;
    //向量内积： 向量 点乘 向量 = 单个值
    Type dot(const Vector<Type>& other_vector) const;
    //向量叉积，向量 *向量 = 矩阵
    Matrix<Type> direct(const Vector<Type>& other_vector) const;
    //该向量生成对角矩阵，主对角线元素就是该向量
    Matrix<Type> arrange_diagonal_matrix(void) const;

///对自己向量元素进行处理
    Vector<Type> calculate_absolute_value(void) const;  //返回当前向量的绝对值向量
    //将向量中低于给定lower_bound的元素替换成lower_bound
    Vector<Type> calculate_lower_bounded(const Type& lower_bound) const;
    Vector<Type> calculate_lower_bounded(const Vector<Type>& lower_bound) const;
    //将向量中大于给定upper_bound的元素替换成upper_bound
    Vector<Type> calculate_upper_bounded(const Type& upper_bound) const;
    Vector<Type> calculate_upper_bounded(const Vector<Type>& upper_bound) const;
    Vector<Type> calculate_lower_upper_bounded(const Type& lower_bound, const Type& upper_bound) const;
    Vector<Type> calculate_lower_upper_bounded(const Vector<Type>& lower_bound, const Vector<Type>& upper_bound) const;
    void apply_absolute_value(void);    //使得当前向量成为绝对值向量
    void apply_lower_bound(const Type& lower_bound);
    void apply_lower_bound(const Vector<Type>& lower_bound);
    void apply_upper_bound(const Type& upper_bound);
    void apply_upper_bound(const Vector<Type>& upper_bound);
    void apply_lower_upper_bounds(const Type& lower_bound, const Type& upper_bound);
    void apply_lower_upper_bounds(const Vector<Type>& lower_bound, const Vector<Type>& upper_bound);
    inline Vector<Type> operator + (const Type& scalar) const;  //所有元素同加一个标量
    inline Vector<Type> operator + (const Vector<Type>& other_vector) const;
    inline Vector<Type> operator - (const Type& scalar) const;
    inline Vector<Type> operator - (const Vector<Type>& other_vector) const;
    inline Vector<Type> operator * (const Type& scalar) const;
    inline Vector<Type> operator * (const Vector<Type>& other_vector) const;
    Vector<Type> operator / (const Type& scalar) const;
    Vector<Type> operator / (const Vector<Type>& other_vector) const;
    void operator += (const Type& value);
    void operator += (const Vector<Type>& other_vector);
    void operator -= (const Type& value);
    void operator -= (const Vector<Type>& other_vector);
    void operator *= (const Type& value);
    void operator *= (const Vector<Type>& other_vector);
    void operator /= (const Type& value);
    void operator /= (const Vector<Type>& other_vector);
    //other_vector插入到指定位置position
    void tuck_in(const unsigned int& position, const Vector<Type>& other_vector);
    //原向量中抽取出指定长度的向量
    Vector<Type> take_out(const unsigned int& position, const unsigned int& other_size) const;

///序列化
    void load(const std::string& filename);
    void save(const std::string& filename) const;
    //两个向量合并
    Vector<Type> get_assembly(const Vector<Type>& other_vector) const;
    //将to_string解析成vector对象
    void parse(const std::string& str);
    std::string to_string(void) const;
    Vector<std::string> get_string_vector(void) const;
    Matrix<Type> to_matrix(const unsigned int& rows_number, const unsigned int& columns_number) const;

    //柱状图，共bins_number个区间，返回两个vector的一个vector，一个是该区间的频率，一个是区间中心值
    Vector< Vector<Type> > calculate_histogram(const unsigned int& bins_number) const;
    Vector< Vector<Type> > calculate_histogram(void) const; //bins_number=10的特例

private:
    //计算随机数
    double calculate_random_uniform(const double& minimum, double maximum) const;
    double calculate_random_normal(const double& mean, double standard_deviation) const;
};


// Input operator

/// This method re-writes the inputs operator >> for the Vector template.
/// @param is Input stream.
/// @param v Input vector.

template<typename Type>
std::istream& operator >> (std::istream& is, Vector<Type>& v)
{
   const unsigned int size = v.size();

   for(unsigned int i = 0; i < size; i++)
   {
      is >> v[i];
   }

   return(is);
}


// Output operator

/// This method re-writes the outputs operator << for the Vector template.
/// @param os Output stream.
/// @param v Output vector.

template<typename Type>
inline std::ostream& operator << (std::ostream& os, const Vector<Type>& v)
{
   const unsigned int size = v.size();

   if(size > 0)
   {
      for(unsigned int i = 0; i < size-1; i++)
      {
         os << v[i] << " ";
      }

      os << v[size-1];
   }

   return(os);
}


template<typename Type>
inline std::ostream& operator << (std::ostream& os, const Vector< Vector<Type> >& v)
{
   for(unsigned int i = 0; i < v.size(); i++)
   {
      os << "Subvector " << i  << "\n"
         << v[i] << std::endl;
   }

   return(os);
}


template<typename Type>
inline std::ostream& operator << (std::ostream& os, const Vector< Matrix<Type> >& v)
{
   for(unsigned int i = 0; i < v.size(); i++)
   {
      os << "Submatrix" << i  << "\n"
         << v[i];
   }

   return(os);
}


// CONSTRUCTORS

/// Default constructor. It creates a vector of size zero.
template<typename Type>
Vector<Type>::Vector(void) : std::vector<Type>()
{
}


/// General constructor. It creates a vector of size n, containing n copies of the default value for Type.
/// @param new_size Size of vector.
template<typename Type>
Vector<Type>::Vector(const unsigned int& new_size) : std::vector<Type>(new_size)
{
}


/// Constant reference initialization constructor.
/// It creates a vector of size n, containing n copies of the type value of Type.
/// @param new_size Size of Vector.
/// @param value Initialization value of Type.
template<typename Type>
Vector<Type>::Vector(const unsigned int& new_size, const Type& value) : std::vector<Type>(new_size, value)
{
}


/// File constructor. It creates a vector object by loading its members from a data file.
/// @param filename Name of vector data file.
template<typename Type>
Vector<Type>::Vector(const std::string& filename) : std::vector<Type>()
{
   load(filename);
}


/// Sequential constructor.
template<typename Type>
Vector<Type>::Vector(const Type& first, const int& step, const Type& last) : std::vector<Type>()
{
   if(first > last && step > 0 )
   {
   }
   else if(first < last && step < 0)
   {
   }
   else
   {
      const unsigned int new_size = 1 + (unsigned int)((last - first)/step + 0.5);

      this->resize(new_size);

      for(unsigned int i = 0; i < new_size; i++)
      {
         (*this)[i] = first + i*step;
      }
   }
}


/// Input iterators constructor
template<typename Type>
template<class InputIterator>
Vector<Type>::Vector(InputIterator first, InputIterator last) : std::vector<Type>(first, last)
{
}


/// Copy constructor. It creates a copy of an existing Vector.
/// @param other_vector Vector to be copied.
template<typename Type>
Vector<Type>::Vector(const Vector<Type>& other_vector) : std::vector<Type>(other_vector)
{
}


// DESTRUCTOR

/// Destructor.
template<typename Type>
Vector<Type>::~Vector(void)
{
}


// bool operator == (const Type&) const

/// Equal to operator between this vector and a Type value.
/// It produces true if all the elements of this vector are equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.
template<typename Type>
inline bool Vector<Type>::operator == (const Type& value) const
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] != value)
      {
         return(false);
      }
   }

   return(true);
}


// bool operator != (const Type&) const

/// Not equivalent relational operator between this vector and a Type value.
/// It produces true if some element of this vector is not equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.
template<typename Type>
inline bool Vector<Type>::operator != (const Type& value) const
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] != value)
      {
         return(true);
      }
   }

   return(false);
}


// bool operator > (const Type&) const

/// Greater than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are greater than the Type value, and false otherwise.
/// @param value Type value to be compared with.
template<typename Type>
inline bool Vector<Type>::operator > (const Type& value) const
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] <= value)
      {
         return(false);
      }
   }

   return(true);
}


// bool operator < (const Type&) const

/// Less than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are less than the Type value, and false otherwise.
/// @param value Type value to be compared with.
template<typename Type>
inline bool Vector<Type>::operator < (const Type& value) const
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] >= value)
      {
         return(false);
      }
   }

   return(true);
}


// bool operator >= (const Type&) const

/// Greater than or equal to than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are greater than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.
template<typename Type>
inline bool Vector<Type>::operator >= (const Type& value) const
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < value)
      {
         return(false);
      }
   }

   return(true);
}


// bool operator <= (const Type&) const

/// Less than or equal to than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are less than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.
template<typename Type>
inline bool Vector<Type>::operator <= (const Type& value) const
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] > value)
      {
         return(false);
      }
   }

   return(true);
}


// METHODS

// void set(void) method

/// This method sets the size of a vector to zero.
template<typename Type>
void Vector<Type>::set(void)
{
   this->resize(0);
}


// void set(unsigned int) method

/// This method sets a new size to the vector. It does not initialize the data.
/// @param new_size Size for the vector.
template<typename Type>
void Vector<Type>::set(const unsigned int& new_size)
{
   this->resize(new_size);
}


// void set(const unsigned int&, const Type&) method

/// This method sets a new size to the vector and initializes all its elements with a given value.
/// @param new_size Size for the vector.
/// @param new_value Value for all the elements.
template<typename Type>
void set(const unsigned int& new_size, const Type& new_value)
{
   vector<Type>::resize(new_size);

   initialize(new_value);
}


// void set(const std::string&) method

/// This method sets all the members of a vector object by loading them from a data file.
/// The format is specified in the OpenNN manual.
/// @param filename Name of vector data file.
template<typename Type>
void Vector<Type>::set(const std::string& filename)
{
   load(filename);
}


// void set(const Type&, const int&, const Type&) method

/// This method makes this vector to have elements starting from a given value, continuing with a step value and finishing with a given value.
/// Depending on the starting, step and finishin values, this method can produce a variety of sizes and data.
/// @param first Starting value.
/// @param step Step value.
/// @param last Finishing value.
template<typename Type>
void Vector<Type>::set(const Type& first, const int& step, const Type& last)
{
   if(first > last && step > 0 )
   {
      this->resize(0);
   }
   else if(first < last && step < 0)
   {
      this->resize(0);
   }
   else
   {
      const unsigned int new_size = 1 + (unsigned int)((last - first)/step + 0.5);

      this->resize(new_size);

      for(unsigned int i = 0; i < new_size; i++)
      {
         (*this)[i] = first + i*step;
      }
   }
}


// void set(const Type&, const double&, const Type&) method

/// This method makes this vector to have elements starting from a given value, continuing with a step value and finishing with a given value.
/// Depending on the starting, step and finishin values, this method can produce a variety of sizes and data.
/// @param first Starting value.
/// @param step Step value.
/// @param last Finishing value.
template<typename Type>
void Vector<Type>::set(const Type& first, const double& step, const Type& last)
{
   if(first > last && step > 0 )
   {
      this->resize(0);
   }
   else if(first < last && step < 0)
   {
      this->resize(0);
   }
   else
   {
      const unsigned int new_size = 1 + (unsigned int)((last - first)/step + 0.5);

      this->resize(new_size);

      for(unsigned int i = 0; i < new_size; i++)
      {
         (*this)[i] = first + i*step;
      }
   }
}


// void set(const Vector&) method

/// This method sets the members of this object with the values of another vector.
/// @param other_vector Object to set this vector.
template<typename Type>
void Vector<Type>::set(const Vector& other_vector)
{
   *this = other_vector;
}


// void initialize(const Type&) method

/// This method initializes all the elements of the vector with a given value.
/// @param value Type value.
template<typename Type>
void Vector<Type>::initialize(const Type& value)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] = value;
   }
}


// void initialize_sequential(void) method

/// This method initializes all the elements of the vector in a sequential order.
template<typename Type>
void Vector<Type>::initialize_sequential(void)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] = i;
   }
}


// void initialize_uniform(void) method

/// This method assigns a random value comprised between -1 and 1 to each element in the vector.
template<typename Type>
void Vector<Type>::initialize_uniform(void)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_uniform(-1.0, 1.0);
   }
}


// void initialize_uniform(const double&, const double&) method

/// This method assigns a random value comprised between a minimum value and a maximum value to each element in
/// the vector.
/// @param minimum Minimum initialization value.
/// @param maximum Maximum initialization value.
template<typename Type>
void Vector<Type>::initialize_uniform(const double& minimum, double maximum)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_uniform(minimum, maximum);
   }
}


// void initialize_uniform(const Vector<double>&, const Vector<double>&) method

/// This method assigns a random value comprised between given minimum and a maximum values to every element in the
/// vector.
/// @param minimum Minimum initialization values.
/// @param maximum Maximum initialization values.
template<typename Type>
void Vector<Type>::initialize_uniform(const Vector<double>& minimum, const Vector<double>& maximum)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_uniform(minimum[i], maximum[i]);
   }
}


// void initialize_normal(void) method

/// This method assigns random values to each element in the vector. These are taken from a normal distribution with
/// mean 0 and standard deviation 1.
template<typename Type>
void Vector<Type>::initialize_normal(void)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_normal(0.0, 1.0);
   }
}


// void initialize_normal(const double&, const double&) method

/// This method assigns random values to each element in the vector.
/// These are taken from a normal distribution with single mean and standard deviation values for all the elements.
/// @param mean Mean value of uniform distribution.
/// @param standard_deviation Standard deviation value of uniform distribution.
template<typename Type>
void Vector<Type>::initialize_normal(const double& mean, double standard_deviation)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_normal(mean, standard_deviation);
   }
}


// void initialize_normal(const Vector<double>, const Vector<double>) method

/// This method assigns random values to each element in the vector.
/// These are taken from normal distributions with given means and standard deviations for each element.
/// @param mean Mean values of normal distributions.
/// @param standard_deviation Standard deviation values of normal distributions.
template<typename Type>
void Vector<Type>::initialize_normal(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_normal(mean[i], standard_deviation[i]);
   }
}


// Type calculate_minimum(void) const method

/// This method returns the smallest element in the vector.
template<typename Type>
Type Vector<Type>::calculate_minimum(void) const
{
   const unsigned int this_size = this->size();

   Type minimum = (*this)[0];

   for(unsigned int i = 1; i < this_size; i++)
   {
      if((*this)[i] < minimum)
      {
         minimum = (*this)[i];
      }
   }

   return(minimum);
}


// Type calculate_maximum(void) const method

/// This method returns the largest element in the vector.
template<typename Type>
Type Vector<Type>::calculate_maximum(void) const
{
   const unsigned int this_size = this->size();

   Type maximum = (*this)[0];

   for(unsigned int i = 1; i < this_size; i++)
   {
      if((*this)[i] > maximum)
      {
         maximum = (*this)[i];
      }
   }

   return(maximum);
}


// Vector<Type> calculate_minimum_maximum(void) const method

/// This method returns a vector containing the smallest and the largest elements in the vector.
template<typename Type>
Vector<Type> Vector<Type>::calculate_minimum_maximum(void) const
{
   unsigned int this_size = this->size();

   Type minimum = (*this)[0];
   Type maximum = (*this)[0];

   for(unsigned int i = 1; i < this_size; i++)
   {
      if((*this)[i] < minimum)
      {
         minimum = (*this)[i];
      }

      if((*this)[i] > maximum)
      {
         maximum = (*this)[i];
      }
   }

   Vector<Type> minimum_maximum(2);
   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// Vector< Vector<Type> > calculate_histogram(const unsigned int&) const method

/// This method bins the elements of the vector into a given number of equally spaced containers.
/// It returns a vector of two vectors.
/// The size of both subvectors is the number of bins.
/// The first subvector contains the frequency of the bins.
/// The second subvector contains the center of the bins.
template<typename Type>
Vector< Vector<Type> > Vector<Type>::calculate_histogram(const unsigned int& bins_number) const
{
   Vector<Type> bins_minimum(bins_number);
   Vector<Type> bins_maximum(bins_number);

   Vector<Type> bins_center(bins_number);
   Vector<Type> bins_frequency(bins_number, 0);

   const Vector<Type> minimum_maximum = calculate_minimum_maximum();

   const Type minimum = minimum_maximum[0];
   const Type maximum = minimum_maximum[1];

   const double bin_length = (maximum-minimum)/((double)bins_number);

   bins_minimum[0] = minimum;
   bins_maximum[0] = minimum + bin_length;
   bins_center[0] = (bins_maximum[0] + bins_minimum[0])/2.0;

   // Calculate bins center

   for(unsigned int i = 1; i < bins_number; i++)
   {
      bins_minimum[i] = bins_minimum[i-1] + bin_length;
      bins_maximum[i] = bins_maximum[i-1] + bin_length;

      bins_center[i] = (bins_maximum[i] + bins_minimum[i])/2.0;
   }

   // Calculate bins frequency

   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < bins_center[0])
      {
         bins_frequency[0]++;
      }

      for(unsigned int j = 1; j < bins_number-1; j++)
      {
         if((*this)[i] >= bins_minimum[j] && (*this)[i] < bins_maximum[j])
         {
            bins_frequency[j]++;
         }
      }

      if((*this)[i] >= bins_center[bins_number-1])
      {
         bins_frequency[bins_number-1]++;
      }
   }

   Vector< Vector<Type> > histogram(2);

   histogram[0] = bins_frequency;
   histogram[1] = bins_center;

   return(histogram);
}


// Vector< Vector<Type> > calculate_histogram(void) const method

/// This method bins the elements of the vector into 10 equally spaced containers.
/// It returns a vector of two vectors.
/// The size of both subvectors is the number of bins (10).
/// The first subvector contains the frequency of the bins.
/// The second subvector contains the center of the bins.
template<typename Type>
Vector< Vector<Type> > Vector<Type>::calculate_histogram(void) const
{
    return(calculate_histogram(10));
}


// unsigned int calculate_minimal_index(void) const method

/// This method returns the index of the smallest element in the vector.
template<typename Type>
unsigned int Vector<Type>::calculate_minimal_index(void) const
{
   const unsigned int this_size = this->size();

   Type minimum = (*this)[0];
   unsigned int minimal_index = 0;

   for(unsigned int i = 1; i < this_size; i++)
   {
      if((*this)[i] < minimum)
      {
         minimum = (*this)[i];
         minimal_index = i;
      }
   }

   return(minimal_index);
}


// unsigned int calculate_maximal_index(void) const method

/// This method returns the index of the largest element in the vector.
template<typename Type>
unsigned int Vector<Type>::calculate_maximal_index(void) const
{
   const unsigned int this_size = this->size();

   Type maximum = (*this)[0];
   unsigned int maximal_index = 0;

   for(unsigned int i = 1; i < this_size; i++)
   {
      if((*this)[i] > maximum)
      {
         maximum = (*this)[i];
         maximal_index = i;
      }
   }

   return(maximal_index);
}


// Vector<unsigned int> calculate_minimal_maximal_index(void) const method

/// This method returns a vector with the indexes of the smallest and the largest elements in the vector.
template<typename Type>
Vector<unsigned int> Vector<Type>::calculate_minimal_maximal_index(void) const
{
   unsigned int this_size = this->size();

   Type minimum = (*this)[0];
   Type maximum = (*this)[0];

   unsigned int minimal_index = 0;
   unsigned int maximal_index = 0;

   for(unsigned int i = 1; i < this_size; i++)
   {
      if((*this)[i] < minimum)
      {
         minimum = (*this)[i];
         minimal_index = i;
      }
      if((*this)[i] > maximum)
      {
         maximum = (*this)[i];
         maximal_index = i;
      }
   }

   Vector<unsigned int> minimal_maximal_index(2);
   minimal_maximal_index[0] = minimal_index;
   minimal_maximal_index[1] = maximal_index;

   return(minimal_maximal_index);
}


// Vector<double> calculate_pow(const Type&) const method

/// This method returns a vector with the elements of this vector raised to a power exponent.
/// @param exponent Pow exponent.
template<typename Type>
Vector<Type> Vector<Type>::calculate_pow(const Type& exponent) const
{
   const unsigned int this_size = this->size();

   Vector<Type> power(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      power[i] = pow((*this)[i], exponent);
   }

   return(power);
}


// Vector<double> calculate_competitive(void) const method

/// This method returns the competitive vector of this vector,
/// whose elements are one the bigest element of this vector, and zero for the other elements.
template<typename Type>
Vector<Type> Vector<Type>::calculate_competitive(void) const
{
   const unsigned int this_size = this->size();

   Vector<Type> competitive(this_size, 0);

   const unsigned int maximal_index = calculate_maximal_index();

   competitive[maximal_index] = 1;

   return(competitive);
}


// Vector<Type> calculate_softmax(void) const method

/// This method returns the softmax vector of this vector,
/// whose elements sum one, and can be interpreted as probabilities.
template<typename Type>
Vector<Type> Vector<Type>::calculate_softmax(void) const
{
   const unsigned int this_size = this->size();

   Vector<Type> softmax(this_size);

   Type sum = 0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      sum += exp((*this)[i]);
   }

   for(unsigned int i = 0; i < this_size; i++)
   {
      softmax[i] = exp((*this)[i])/sum;
   }

   return(softmax);
}


// Matrix<Type> calculate_softmax_Jacobian(void) const method

/// This method returns the softmax Jacobian of this vector.
/// @todo
template<typename Type>
Matrix<Type> Vector<Type>::calculate_softmax_Jacobian(void) const
{
   const unsigned int this_size = this->size();

   Matrix<Type> softmax_Jacobian(this_size, this_size);

   return(softmax_Jacobian);
}



// Vector<bool> calculate_binary(void) const method

/// This method converts the values of the vector to be binary.
/// The threshold value used is 0.5.
template<typename Type>
Vector<bool> Vector<Type>::calculate_binary(void) const
{
   const unsigned int this_size = this->size();

   Vector<bool> binary(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < 0.5)
      {
         binary[i] = false;
      }
      else
      {
         binary[i] = true;
      }
   }

   return(binary);
}


// unsigned int calculate_cumulative_index(const Type&) const method

/// This method applies only to cumulative vectors.
/// It returns the index of the first element which is greater than a given value.
/// @param value Value.
template<typename Type>
unsigned int Vector<Type>::calculate_cumulative_index(const Type& value) const
{
   const unsigned int this_size = this->size();

   if(value <= (*this)[0])
   {
      return(0);
   }

   for(unsigned int i = 1; i < this_size; i++)
   {
      if(value > (*this)[i-1] && value <= (*this)[i])
      {
         return(i);
      }
   }

   return(this_size-1);
}


// unsigned int calculate_closest_index(const Type&) const method

/// This method returns the index of the closest element in the vector to a given value.
template<typename Type>
unsigned int Vector<Type>::calculate_closest_index(const Type& value) const
{
   const Vector<Type> difference = (*this - value).calculate_absolute_value();

   const unsigned int closest_index = difference.calculate_minimal_index();

   return(closest_index);
}


// Type calculate_sum(void) const method

/// This method returns the sum of the elements in the vector.
template<typename Type>
Type Vector<Type>::calculate_sum(void) const
{
   const unsigned int this_size = this->size();

   Type sum = 0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      sum += (*this)[i];
   }

   return(sum);
}


// Type calculate_product(void) const method

/// This method returns the product of the elements in the vector.
template<typename Type>
Type Vector<Type>::calculate_product(void) const
{
   const unsigned int this_size = this->size();

   Type product = 1;

   for(unsigned int i = 0; i < this_size; i++)
   {
      product *= (*this)[i];
   }

   return(product);
}


// double calculate_mean(void) const method

/// This method returns the mean of the elements in the vector.
template<typename Type>
double Vector<Type>::calculate_mean(void) const
{
   const unsigned int this_size = this->size();

   const Type sum = calculate_sum();

   const double mean = sum/(double)this_size;

   return(mean);
}


// double calculate_standard_deviation(void) method

/// This method returns the standard deviation of the elements in the vector.
template<typename Type>
double Vector<Type>::calculate_standard_deviation(void) const
{
   const unsigned int this_size = this->size();

   const double mean = calculate_mean();

   double sum = 0.0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      sum += ((*this)[i] - mean)*((*this)[i] - mean);
   }

   const double standard_deviation = sqrt(sum/(double)this_size);

   return(standard_deviation);
}


// Vector<double> calculate_standard_deviation(void) const method

/// This method returns the mean and the standard deviation of the elements in the vector.
template<typename Type>
Vector<double> Vector<Type>::calculate_mean_standard_deviation(void) const
{
   const unsigned int this_size = this->size();

   const double mean = calculate_mean();

   double sum = 0.0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      sum += ((*this)[i] - mean)*((*this)[i] - mean);
   }

   const double standard_deviation = sqrt(sum/(double)this_size);

   Vector<double> mean_standard_deviation(2);
   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// Vector<double> calculate_statistics(void) const method

/// This method returns the minimum, maximum, mean and the standard deviation of the elements in the vector.
template<typename Type>
Vector<double> Vector<Type>::calculate_statistics(void) const
{
   unsigned int this_size = this->size();

   return(calculate_minimum_maximum().get_assembly(calculate_mean_standard_deviation()));
}


// double calculate_norm(void) const method

/// This element returns the vector norm.
template<typename Type>
double Vector<Type>::calculate_norm(void) const
{
   const unsigned int this_size = this->size();

   double norm = 0.0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      norm += (*this)[i]*(*this)[i];
   }

   norm = sqrt(norm);

   return(norm);
}


// double calculate_distance(const Vector<double>&) const method

/// This method returns the distance between the elements of this vector and the elements of another vector.
/// @param other_vector Other vector.
template<typename Type>
double Vector<Type>::calculate_distance(const Vector<double>& other_vector) const
{
   const unsigned int this_size = this->size();

   double sum_squared_error = 0.0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      sum_squared_error += ((*this)[i] - other_vector[i])*((*this)[i] - other_vector[i]);
   }

   return(sqrt(sum_squared_error));
}


// double calculate_sum_squared_error(const Vector<double>&) const method

/// This method returns the sum squared error between the elements of this vector and the elements of another vector.
/// @param other_vector Other vector.
template<typename Type>
double Vector<Type>::calculate_sum_squared_error(const Vector<double>& other_vector) const
{
   const unsigned int this_size = this->size();

   double sum_squared_error = 0.0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      sum_squared_error += ((*this)[i] - other_vector[i])*((*this)[i] - other_vector[i]);
   }

   return(sum_squared_error);
}


// double calculate_Minkowski_error(const Vector<double>&) const method

/// This method returns the Minkowski squared error between the elements of this vector and the elements of another vector.
/// @param other_vector Other vector.
/// @param Minkowski_parameter Minkowski exponent.
template<typename Type>
double Vector<Type>::calculate_Minkowski_error(const Vector<double>& other_vector, double Minkowski_parameter) const
{
   const unsigned int this_size = this->size();

   double Minkowski_error = 0.0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      Minkowski_error += pow((*this)[i] - other_vector[i], Minkowski_parameter);
   }

   return(Minkowski_error);
}


// void calculate_absolute_value(void) const method

/// This method returns a vector with the absolute values of the current vector.
template<typename Type>
Vector<Type> Vector<Type>::calculate_absolute_value(void) const
{
   const unsigned int this_size = this->size();

   Vector<Type> absolute_value(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] > 0)
      {
         absolute_value[i] = (*this)[i];
      }
      else
      {
         absolute_value[i] = -(*this)[i];
      }
   }

   return(absolute_value);
}


// void apply_absolute_value(void) method

/// This method sets the elements of the vector to their absolute values.
template<typename Type>
void Vector<Type>::apply_absolute_value(void)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < 0)
      {
         (*this)[i] = -(*this)[i];
      }
   }
}


// Vector<Type> calculate_lower_bounded(const Type&) const method

/// This method returns a vector with the bounded elements from below of the current vector.
/// @param lower_bound Lower bound values.
template<typename Type>
Vector<Type> Vector<Type>::calculate_lower_bounded(const Type& lower_bound) const
{
   const unsigned int this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound)
      {
         bounded_vector[i] = lower_bound;
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_bounded(const Vector<Type>&) const method

/// This method returns a vector with the bounded elements from above of the current vector.
/// @param lower_bound Lower bound values.
template<typename Type>
Vector<Type> Vector<Type>::calculate_lower_bounded(const Vector<Type>& lower_bound) const
{
   const unsigned int this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   // Apply lower bound

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound[i])
      {
         bounded_vector[i] = lower_bound[i];
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_upper_bounded(const Type&) const method

/// This method bounds the elements of the vector if they fall above an upper bound value.
/// @param upper_bound Upper bound value.
template<typename Type>
Vector<Type> Vector<Type>::calculate_upper_bounded(const Type& upper_bound) const
{
   const unsigned int this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] > upper_bound)
      {
         bounded_vector[i] = upper_bound;
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_upper_bounded(const Vector<Type>&) const method

/// This method bounds the elements of the vector if they fall above their corresponding upper bound values.
/// @param upper_bound Upper bound values.
template<typename Type>
Vector<Type> Vector<Type>::calculate_upper_bounded(const Vector<Type>& upper_bound) const
{
   const unsigned int this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   // Apply upper bound

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] > upper_bound[i])
      {
         bounded_vector[i] = upper_bound[i];
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_upper_bounded(const Type&, const Type&) const method

/// This method bounds the elements of the vector if they fall above or below their lower or upper
/// bound values, respectively.
/// @param lower_bound Lower bound value.
/// @param upper_bound Upper bound value.
template<typename Type>
Vector<Type> Vector<Type>::calculate_lower_upper_bounded(const Type& lower_bound, const Type& upper_bound) const
{
   const unsigned int this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound)
      {
         bounded_vector[i] = lower_bound;
      }
      else if((*this)[i] > upper_bound)
      {
         bounded_vector[i] = upper_bound;
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_upper_bounded(const Vector<Type>&, const Vector<Type>&) const method

/// This method bounds the elements of the vector if they fall above or below their corresponding lower or upper
/// bound values, respectively.
/// @param lower_bound Lower bound values.
/// @param upper_bound Upper bound values.
template<typename Type>
Vector<Type> Vector<Type>::calculate_lower_upper_bounded(const Vector<Type>& lower_bound, const Vector<Type>& upper_bound) const
{
   const unsigned int this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   // Apply lower and upper bounds

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound[i])
      {
         bounded_vector[i] = lower_bound[i];
      }
      else if((*this)[i] > upper_bound[i])
      {
         bounded_vector[i] = upper_bound[i];
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// void apply_lower_bound(const Type&) method

/// This method sets the elements of the vector to a given value if they fall below that value.
/// @param lower_bound Lower bound value.
template<typename Type>
void Vector<Type>::apply_lower_bound(const Type& lower_bound)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound)
      {
         (*this)[i] = lower_bound;
      }
   }
}


// void apply_lower_bound(const Vector<Type>&) method

/// This method sets the elements of the vector to given values if they fall below that values.
/// @param lower_bound Lower bound values.
template<typename Type>
void Vector<Type>::apply_lower_bound(const Vector<Type>& lower_bound)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound[i])
      {
         (*this)[i] = lower_bound[i];
      }
   }
}


// void apply_upper_bound(const Type&) method

/// This method sets the elements of the vector to a given value if they fall above that value.
/// @param upper_bound Upper bound value.
template<typename Type>
void Vector<Type>::apply_upper_bound(const Type& upper_bound)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] > upper_bound)
      {
         (*this)[i] = upper_bound;
      }
   }
}


// void apply_upper_bound(const Vector<Type>&) method

/// This method sets the elements of the vector to given values if they fall above that values.
/// @param upper_bound Upper bound values.
template<typename Type>
void Vector<Type>::apply_upper_bound(const Vector<Type>& upper_bound)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] > upper_bound[i])
      {
         (*this)[i] = upper_bound[i];
      }
   }
}


// void apply_lower_upper_bounds(const Type&, const Type&) method

/// This method sets the elements of the vector to a given lower bound value if they fall below that value,
/// or to a given upper bound value if they fall above that value.
/// @param lower_bound Lower bound value.
/// @param upper_bound Upper bound value.
template<typename Type>
void Vector<Type>::apply_lower_upper_bounds(const Type& lower_bound, const Type& upper_bound)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound)
      {
         (*this)[i] = lower_bound;
      }
      else if((*this)[i] > upper_bound)
      {
         (*this)[i] = upper_bound;
      }
   }
}


// void apply_lower_upper_bounds(const Vector<Type>&, const Vector<Type>&) method

/// This method sets the elements of the vector to given lower bound values if they fall below that values,
/// or to given upper bound values if they fall above that values.
/// @param lower_bound Lower bound values.
/// @param upper_bound Upper bound values.
template<typename Type>
void Vector<Type>::apply_lower_upper_bounds(const Vector<Type>& lower_bound, const Vector<Type>& upper_bound)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound[i])
      {
         (*this)[i] = lower_bound[i];
      }
      else if((*this)[i] > upper_bound[i])
      {
         (*this)[i] = upper_bound[i];
      }
   }
}


// Vector<Type> operator + (const Type&) const method

/// Sum vector+scalar arithmetic operator.
/// @param scalar Scalar value to be added to this vector.
template<typename Type>
inline Vector<Type> Vector<Type>::operator + (const Type& scalar) const
{
   const unsigned int this_size = this->size();

   Vector<Type> sum(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      sum[i] = (*this)[i] + scalar;
   }

   return(sum);
}


// Vector<Type> operator + (const Vector<Type>&) const method

/// Sum vector+vector arithmetic operator.
/// @param other_vector Vector to be added to this vector.
template<typename Type>
inline Vector<Type> Vector<Type>::operator + (const Vector<Type>& other_vector) const
{
   const unsigned int this_size = this->size();

   Vector<Type> sum(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      sum[i] = (*this)[i] + other_vector[i];
   }

   return(sum);
}


//Vector<Type> operator - (const Type&) const method

/// Difference vector-scalar arithmetic operator.
/// @param scalar Scalar value to be subtracted to this vector.
template<typename Type>
inline Vector<Type> Vector<Type>::operator - (const Type& scalar) const
{
   const unsigned int this_size = this->size();

   Vector<Type> difference(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      difference[i] = (*this)[i] - scalar;
   }

   return(difference);
}


// Vector<Type> operator - (const Vector<Type>&) const method

/// Difference vector-vector arithmetic operator.
/// @param other_vector vector to be subtracted to this vector.
template<typename Type>
inline Vector<Type> Vector<Type>::operator - (const Vector<Type>& other_vector) const
{
   const unsigned int this_size = this->size();

   Vector<Type> difference(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      difference[i] = (*this)[i] - other_vector[i];
   }

   return(difference);
}


// Vector<Type> operator * (const Type&) const method

/// Product vector*scalar arithmetic operator.
/// @param scalar Scalar value to be multiplied to this vector.
template<typename Type>
inline Vector<Type> Vector<Type>::operator * (const Type& scalar) const
{
   const unsigned int this_size = this->size();

   Vector<Type> product(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      product[i] = (*this)[i]*scalar;
   }

   return(product);
}


// Type operator * (const Vector<Type>&) const method

/// Element by element product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.
template<typename Type>
inline Vector<Type> Vector<Type>::operator * (const Vector<Type>& other_vector) const
{
   const unsigned int this_size = this->size();

   Vector<Type> product(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      product[i] = (*this)[i]*other_vector[i];
   }

   return(product);
}


// Matrix<Type> operator * (const Matrix<Type>&) const method

/// Element by row product vector*matrix arithmetic operator.
/// @param matrix matrix to be multiplied to this vector.
template<typename Type>
inline Matrix<Type> Vector<Type>::operator * (const Matrix<Type>& matrix) const
{
   const unsigned int rows_number = matrix.get_rows_number();
   const unsigned int columns_number = matrix.get_columns_number();

   Matrix<Type> product(rows_number, columns_number);

   for(unsigned int i = 0; i < rows_number; i++)
   {
      for(unsigned int j = 0; j < columns_number; j++)
      {
         product[i][j] = (*this)[i]*matrix[i][j];
      }
   }

   return(product);
}


// Vector<Type> dot(const Matrix<Type>&) const method

/// This method returns the dot product of this vector with a matrix.
/// The number of rows of the matrix must be equal to the size of the vector.
/// @param matrix matrix to be multiplied to this vector.
template<typename Type>
Vector<Type> Vector<Type>::dot(const Matrix<Type>& matrix) const
{
   const unsigned int rows_number = matrix.get_rows_number();

   const unsigned int columns_number = matrix.get_columns_number();

   Vector<Type> product(columns_number);

   for(unsigned int j = 0; j < columns_number; j++)
   {
      product[j] = 0;

      for(unsigned int i = 0; i < rows_number; i++)
      {
         product[j] += (*this)[i]*matrix[i][j];
      }
   }

   return(product);
}


// Vector<Type> dot(const Vector<Type>&) const method

/// Dot product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.
template<typename Type>
Type Vector<Type>::dot(const Vector<Type>& other_vector) const
{
   const unsigned int this_size = this->size();

   Type dot_product = 0;

   for(unsigned int i = 0; i < this_size; i++)
   {
      dot_product += (*this)[i]*other_vector[i];
   }

   return(dot_product);
}


// Matrix<Type> direct(const Vector<Type>&) const method

/// Outer product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.
template<typename Type>
Matrix<Type> Vector<Type>::direct(const Vector<Type>& other_vector) const
{
   const unsigned int this_size = this->size();

   Matrix<Type> direct(this_size, this_size);

   // Upper diagonal

   for(unsigned int i = 0;  i < this_size; i++)
   {
      for(unsigned int j = i;  j < this_size; j++)
      {
         direct[i][j] = (*this)[i]*other_vector[j];
      }
   }

   // Symmetry

   for(unsigned int i = 0; i < this_size; i++)
   {
      for(unsigned int j = 0; j < i; j++)
      {
         direct[i][j] = direct[j][i];
      }
   }

   return(direct);
}


//Vector<Type> operator / (const Type&) const method

/// Cocient vector/scalar arithmetic operator.
/// @param scalar Scalar value to be divided to this vector.
template<typename Type>
Vector<Type> Vector<Type>::operator / (const Type& scalar) const
{
   const unsigned int this_size = this->size();

   Vector<Type> cocient(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      cocient[i] = (*this)[i]/scalar;
   }

   return(cocient);
}


// Vector<Type> operator / (const Vector<Type>&) const method

/// Cocient vector/vector arithmetic operator.
/// @param other_vector vector to be divided to this vector.
template<typename Type>
Vector<Type> Vector<Type>::operator / (const Vector<Type>& other_vector) const
{
   const unsigned int this_size = this->size();

   Vector<Type> cocient(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      cocient[i] = (*this)[i]/other_vector[i];
   }

   return(cocient);
}


// void operator += (const Type&)

/// Scalar sum and assignment operator.
/// @param value Scalar value to be added to this vector.
template<typename Type>
void Vector<Type>::operator += (const Type& value)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] += value;
   }
}


// void operator += (const Vector<Type>&)

/// Vector sum and assignment operator.
/// @param other_vector Vector to be added to this vector.
template<typename Type>
void Vector<Type>::operator += (const Vector<Type>& other_vector)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] += other_vector[i];
   }
}


// void operator -= (const Type&)

/// Scalar rest and assignment operator.
/// @param value Scalar value to be subtracted to this vector.
template<typename Type>
void Vector<Type>::operator -= (const Type& value)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] -= value;
   }
}


// void operator -= (const Vector<Type>&)

/// Vector rest and assignment operator.
/// @param other_vector Vector to be subtracted to this vector.
template<typename Type>
void Vector<Type>::operator -= (const Vector<Type>& other_vector)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] -= other_vector[i];
   }
}


// void operator *= (const Type&)

/// Scalar product and assignment operator.
/// @param value Scalar value to be multiplied to this vector.
template<typename Type>
void Vector<Type>::operator *= (const Type& value)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] *= value;
   }
}


// void operator *= (const Vector<Type>&)

/// Vector product and assignment operator.
/// @param other_vector Vector to be multiplied to this vector.
template<typename Type>
void Vector<Type>::operator *= (const Vector<Type>& other_vector)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] *= other_vector[i];
   }
}


// void operator /= (const Type&)

/// Scalar division and assignment operator.
/// @param value Scalar value to be divided to this vector.
template<typename Type>
void Vector<Type>::operator /= (const Type& value)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] /= value;
   }
}


// void operator /= (const Vector<Type>&)

/// Vector division and assignment operator.
/// @param other_vector Vector to be divided to this vector.
template<typename Type>
void Vector<Type>::operator /= (const Vector<Type>& other_vector)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      (*this)[i] /= other_vector[i];
   }
}

// void scale_mean_standard_deviation(const Vector<double>&, const Vector<double>&) method

/// This method scales the vector elements with given mean and standard deviation values.
/// It updates the data in the vector.
/// The size of the mean and standard deviation vectors must be equal to the size of the vector.
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.
template<typename Type>
void Vector<Type>::scale_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation)
{
   const unsigned int this_size = this->size();

   // Rescale data

   for(unsigned int i = 0; i < this_size; i++)
   {
      if(standard_deviation[i] < 1e-99)
      {
          std::cout << "Those elements won't be scaled.\n";
         // Do nothing
      }
      else
      {
         (*this)[i] = ((*this)[i] - mean[i])/standard_deviation[i];
      }
   }
}



// Vector<Type> calculate_scaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method

/// This method returns a vector with the scaled elements of this vector acording to the minimum and maximum method.
/// The size of the minimum and maximum vectors must be equal to the size of the vector.
/// @param minimum Minimum values.
/// @param maximum Maximum values.
template<typename Type>
Vector<Type> Vector<Type>::calculate_scaled_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum) const
{
   const unsigned int this_size = this->size();

   Vector<Type> scaled_minimum_maximum(this_size);

   // Rescale data

   for(unsigned int i = 0; i < this_size; i++)
   {
      if(maximum[i] - minimum[i] < 1e-99)
      {
          std::cout << "Those elements won't be scaled.\n";
         scaled_minimum_maximum[i] = (*this)[i];
      }
      else
      {
         scaled_minimum_maximum[i] = 2.0*((*this)[i] - minimum[i])/(maximum[i]-minimum[i])-1.0;
      }
   }

   return(scaled_minimum_maximum);
}


// Vector<Type> calculate_scaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method

/// This method returns a vector with the scaled elements of this vector acording to the mean and standard deviation method.
/// The size of the mean and standard deviation vectors must be equal to the size of the vector.
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.
template<typename Type>
Vector<Type> Vector<Type>::calculate_scaled_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation) const
{
   const unsigned int this_size = this->size();

   Vector<Type> scaled_mean_standard_deviation(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      if(standard_deviation[i] < 1e-99)
      {
          std::cout << "Those elements won't be scaled.\n";
         scaled_mean_standard_deviation = (*this)[i];
      }
      else
      {
         scaled_mean_standard_deviation[i] = (*this)[i]*standard_deviation[i] + mean[i];
      }
   }

   return(scaled_mean_standard_deviation);
}


// Vector<Type> calculate_unscaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method

/// This method returns a vector with the unscaled elements of this vector acording to the minimum and maximum method.
/// The size of the minimum and maximum vectors must be equal to the size of the vector.
/// @param minimum Minimum values.
/// @param maximum Maximum values.
template<typename Type>
Vector<Type> Vector<Type>::calculate_unscaled_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum) const
{
   const unsigned int this_size = this->size();

   Vector<Type> unscaled_minimum_maximum(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      if(maximum[i] - minimum[i] < 1e-99)
      {
          std::cout << "Those elements won't be unscaled.\n";

         unscaled_minimum_maximum[i] = (*this)[i];
      }
      else
      {
    //      unscaled_minimum_maximum[i] = 0.5*((*this)[i] + 1.0)*(maximum[i]-minimum[i]) + minimum[i];
           if ((*this)[i] >= maximum[i])
           {
               unscaled_minimum_maximum[i] = maximum[i];
           }
           else if ((*this)[i] <= minimum[i])
           {
               unscaled_minimum_maximum[i] = minimum[i];
           }
          else{
              unscaled_minimum_maximum[i] = 0.5*((*this)[i] + 1.0)*(maximum[i]-minimum[i]) + minimum[i];
          }
      }
   }

   return(unscaled_minimum_maximum);
}


// Vector<Type> calculate_unscaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method

/// This method returns a vector with the unscaled elements of this vector acording to the mean and standard deviation method.
/// The size of the mean and standard deviation vectors must be equal to the size of the vector.
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.
template<typename Type>
Vector<Type> Vector<Type>::calculate_unscaled_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation) const
{
   const unsigned int this_size = this->size();

   Vector<Type> unscaled_mean_standard_deviation(this_size);

   for(unsigned int i = 0; i < this_size; i++)
   {
      if(standard_deviation[i] < 1e-99)
      {
         std::cout << "Those elements won't be scaled.\n";
         unscaled_mean_standard_deviation[i] = (*this)[i];
      }
      else
      {
         unscaled_mean_standard_deviation[i] = (*this)[i]*standard_deviation[i] + mean[i];
      }
   }

   return(unscaled_mean_standard_deviation);
}


// void scale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method

/// This method scales the vectir elements with given minimum and maximum values.
/// It updates the data in the vector.
/// The size of the minimum and maximum vectors must be equal to the size of the vector.
/// @param minimum Minimum values.
/// @param maximum Maximum values.
template<typename Type>
void Vector<Type>::scale_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum)
{
   const unsigned int this_size = this->size();

   // Rescale data

   for(unsigned int i = 0; i < this_size; i++)
   {
      if(maximum[i] - minimum[i] < 1e-99)
      {
           // Do nothing
      }
      else
      {
         (*this)[i] = 2.0*((*this)[i] - minimum[i])/(maximum[i]-minimum[i])-1.0;
      }
   }
}
//自身进行缩放
template<typename Type>
void Vector<Type>::scale_self_minimum_maximum(void)
{
    Vector<Type> minimum_maximum = calculate_minimum_maximum();
    unsigned int this_size = this->size();
    Type minimum = minimum_maximum[0];
    Type maximum = minimum_maximum[1];
    for(unsigned int i = 0; i < this_size; i++)
    {
        if(maximum - minimum < 1e-99){
            // Do nothing
        }else{
            (*this)[i] = 2.0*((*this)[i] - minimum)/(maximum-minimum)-1.0;
        }
    }
}

// void unscale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method

/// This method unscales the vector elements with given minimum and maximum values.
/// It updates the vector elements.
/// The size of the minimum and maximum vectors must be equal to the size of the vector.
/// @param minimum Minimum values.
/// @param maximum Maximum deviation values.
template<typename Type>
void Vector<Type>::unscale_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if(maximum[i] - minimum[i] < 1e-99)
      {
          std::cout << "Those elements won't be unscaled.\n";
         // Do nothing
      }
      else
      {
          (*this)[i] = 0.5*((*this)[i] + 1.0)*(maximum[i]-minimum[i]) + minimum[i];
           if ((*this)[i] >= maximum[i])
           {
               (*this)[i] = maximum[i];
           }
           else if ((*this)[i] <= minimum[i])
           {
               (*this)[i] = minimum[i];
           }
           else{

           }
      }
   }
}


// void unscale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method

/// This method unscales the vector elements with given mean and standard deviation values.
/// It updates the vector elements.
/// The size of the mean and standard deviation vectors must be equal to the size of the vector.
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.
template<typename Type>
void Vector<Type>::unscale_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation)
{
   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      if(standard_deviation[i] < 1e-99)
      {
         std::cout << "Those elements won't be scaled.\n";
         // Do nothing
      }
      else
      {
         (*this)[i] = (*this)[i]*standard_deviation[i] + mean[i];
      }
   }
}


// Matrix<Type> arrange_diagonal_matrix(void) const method

/// This method returns a squared matrix in which the entries outside the main diagonal are all zero.
/// The elements in the diagonal are the elements in this vector.
template<typename Type>
Matrix<Type> Vector<Type>::arrange_diagonal_matrix(void) const
{
   const unsigned int this_size = this->size();

   Matrix<Type> matrix(this_size, this_size, 0.0);

   for(unsigned int i = 0; i < this_size; i++)
   {
      matrix[i][i] = (*this)[i];
   }

   return(matrix);
}


// void load(const std::string&) method

/// This method loads the members of a vector from an data file.
/// Please be careful with the file format, which is specified in the OpenNN manual.
/// @param filename Name of vector file.
template<typename Type>
void Vector<Type>::load(const std::string& filename)
{
   std::ifstream file(filename.c_str());

   std::stringstream buffer;

   std::string line;

   while(file.good())
   {
      getline(file, line);

      buffer << line;
   }

   std::istream_iterator<std::string> it(buffer);
   std::istream_iterator<std::string> end;

   const std::vector<std::string> results(it, end);

   const unsigned int new_size = results.size();

   this->resize(new_size);

   file.clear();
   file.seekg(0, std::ios::beg);

   // Read data

   for(unsigned int i = 0; i < new_size; i++)
   {
      file >> (*this)[i];
   }

   file.close();
}


// void save(const std::string&) const method

/// This method saves to a data file the elements of the vector.
/// The file format is as follows:
/// element_0 element_1 ... element_N-1
/// @param filename Name of vector data file.
template<typename Type>
void Vector<Type>::save(const std::string& filename) const
{
   std::ofstream file(filename.c_str());

   if(!file.is_open())
   {
      std::ostringstream buffer;
      buffer << "Cannot open vector data file.\n";
      throw std::logic_error(buffer.str());
   }

   // Write file

   const unsigned int this_size = this->size();

   for(unsigned int i = 0; i < this_size; i++)
   {
      file << (*this)[i] << " ";
   }

   file << std::endl;

   // Close file

   file.close();
}


// void tuck_in(const unsigned int&, const Vector<Type>&) const method

/// Insert another vector starting from a given position.
/// @param position Insertion position.
/// @param other_vector Vector to be inserted.
template<typename Type>
void Vector<Type>::tuck_in(const unsigned int& position, const Vector<Type>& other_vector)
{
   const unsigned int other_size = other_vector.size();

   for(unsigned int i = 0; i < other_size; i++)
   {
      (*this)[position + i] = other_vector[i];
   }
}


// Vector<Type> take_out(const unsigned int&, const unsigned int&) method

/// Extract a vector of a given size from a given position
/// @param position Extraction position.
/// @param other_size Size of vector to be extracted.
template<typename Type>
Vector<Type> Vector<Type>::take_out(const unsigned int& position, const unsigned int& other_size) const
{
   Vector<Type> other_vector(other_size);

   for(unsigned int i = 0; i < other_size; i++)
   {
      other_vector[i] = (*this)[position + i];
   }

   return(other_vector);
}


// Vector<Type> get_assembly(const Vector<Type>&) const method

/// Assemble two vectors.
/// @param other_vector Vector to be get_assemblyd to this vector.
template<typename Type>
Vector<Type> Vector<Type>::get_assembly(const Vector<Type>& other_vector) const
{
   const unsigned int this_size = this->size();
   const unsigned int other_size = other_vector.size();

   if(this_size == 0 && other_size == 0)
   {
      Vector<Type> assembly;

      return(assembly);
   }
   else if(this_size == 0)
   {
      return(other_vector);
   }
   else if(other_size == 0)
   {
      return(*this);
   }
   else
   {
      Vector<Type> assembly(this_size + other_size);

      for(unsigned int i = 0; i < this_size; i++)
      {
         assembly[i] = (*this)[i];
      }

      for(unsigned int i = 0; i < other_size; i++)
      {
         assembly[this_size+i] = other_vector[i];
      }

      return(assembly);
   }
}


// void parse(const std::string&) method

/// This method takes a string representation of a vector and sets this vector to have size equal to the number of words and values equal to that words.
/// @param str String to be parsed.
template<typename Type>
void Vector<Type>::parse(const std::string& str)
{
   if(!str.empty())
   {
      std::istringstream buffer(str);

      std::istream_iterator<std::string> first(buffer);
      std::istream_iterator<std::string> last;

      Vector<std::string> str_vector(first, last);

      const  unsigned int new_size = str_vector.size();

      if(new_size > 0)
      {
         this->resize(new_size);

         buffer.clear();
         buffer.seekg(0, std::ios::beg);

         for(unsigned int i = 0; i < new_size; i++)
         {
            buffer >> (*this)[i];
         }
      }
   }
}


// std::string to_string(void)

/// This method returns a string representation of this vector.
template<typename Type>
std::string Vector<Type>::to_string(void) const
{
   std::ostringstream buffer;

   buffer << *this;

   return(buffer.str());
}


// Vector<std::string> get_string_vector(void) const

/// This method retuns a vector of strings with size equal to the size of this vector and elements equal to string representations of the elements of this vector.
template<typename Type>
Vector<std::string> Vector<Type>::get_string_vector(void) const
{
   const unsigned int this_size = this->size();

   Vector<std::string> string_vector(this_size);

   std::ostringstream buffer;

   for(unsigned int i = 0; i < this_size; i++)
   {
      buffer.str("");
      buffer << (*this)[i];

      string_vector[i] = buffer.str();
   }

   return(string_vector);
}


// Matrix<Type> to_matrix(const unsigned int&, const unsigned int&) method

/// This method returns a matrix with given numbers of rows and columns and with the elements of this vector ordered by rows.
/// The number of rows multiplied by the number of columns must be equal to the size of this vector.
/// @param rows_number Number of rows in the new matrix.
/// @param columns_number Number of columns in the new matrix.

template<typename Type>
Matrix<Type> Vector<Type>::to_matrix(const unsigned int& rows_number, const unsigned int& columns_number) const
{
   Matrix<Type> matrix(rows_number, columns_number);

   unsigned int index = 0;

   for(unsigned int i = 0; i < rows_number; i++)
   {
      for(unsigned int j = 0; j < rows_number; j++)
      {
         matrix[i][j] = (*this)[index];
         index++;
      }
   }

   return(matrix);
}

// double calculate_random_uniform(const double&, const double&) method

/// This method returns a random number chosen from a uniform distribution.
/// @param minimum Minimum value.
/// @param maximum Maximum value.
template<typename Type>
double Vector<Type>::calculate_random_uniform(const double& minimum, double maximum) const
{
   const double random = (double)rand()/(RAND_MAX+1.0);

   const double random_uniform = minimum + (maximum-minimum)*random;

   return(random_uniform);
}


// double calculate_random_normal(const double&, const double&) method

/// This method returns a random number chosen from a normal distribution.
/// @param mean Mean value of normal distribution.
/// @param standard_deviation Standard deviation value of normal distribution.
template<typename Type>
double Vector<Type>::calculate_random_normal(const double& mean, double standard_deviation) const
{
   const double pi = 4.0*atan(1.0);

   double random_uniform_1;

   do
   {
      random_uniform_1 = (double)rand()/(RAND_MAX+1.0);

   }while(random_uniform_1 == 0.0);

   const double random_uniform_2 = (double)rand()/(RAND_MAX+1.0);

   // Box-Muller transformation

   const double random_normal = mean + sqrt(-2.0*log(random_uniform_1))*sin(2.0*pi*random_uniform_2)*standard_deviation;

   return(random_normal);
}

#endif
