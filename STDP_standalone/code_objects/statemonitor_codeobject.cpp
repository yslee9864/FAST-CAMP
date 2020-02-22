#include "objects.h"
#include "code_objects/statemonitor_codeobject.h"
#include "brianlib/common_math.h"
#include "brianlib/stdint_compat.h"
#include<cmath>
#include<ctime>
#include<iostream>
#include<fstream>
#include<climits>

////// SUPPORT CODE ///////
namespace {
 	
 template < typename T1, typename T2 > struct _higher_type;
 template < > struct _higher_type<int,int> { typedef int type; };
 template < > struct _higher_type<int,long> { typedef long type; };
 template < > struct _higher_type<int,long long> { typedef long long type; };
 template < > struct _higher_type<int,float> { typedef float type; };
 template < > struct _higher_type<int,double> { typedef double type; };
 template < > struct _higher_type<int,long double> { typedef long double type; };
 template < > struct _higher_type<long,int> { typedef long type; };
 template < > struct _higher_type<long,long> { typedef long type; };
 template < > struct _higher_type<long,long long> { typedef long long type; };
 template < > struct _higher_type<long,float> { typedef float type; };
 template < > struct _higher_type<long,double> { typedef double type; };
 template < > struct _higher_type<long,long double> { typedef long double type; };
 template < > struct _higher_type<long long,int> { typedef long long type; };
 template < > struct _higher_type<long long,long> { typedef long long type; };
 template < > struct _higher_type<long long,long long> { typedef long long type; };
 template < > struct _higher_type<long long,float> { typedef float type; };
 template < > struct _higher_type<long long,double> { typedef double type; };
 template < > struct _higher_type<long long,long double> { typedef long double type; };
 template < > struct _higher_type<float,int> { typedef float type; };
 template < > struct _higher_type<float,long> { typedef float type; };
 template < > struct _higher_type<float,long long> { typedef float type; };
 template < > struct _higher_type<float,float> { typedef float type; };
 template < > struct _higher_type<float,double> { typedef double type; };
 template < > struct _higher_type<float,long double> { typedef long double type; };
 template < > struct _higher_type<double,int> { typedef double type; };
 template < > struct _higher_type<double,long> { typedef double type; };
 template < > struct _higher_type<double,long long> { typedef double type; };
 template < > struct _higher_type<double,float> { typedef double type; };
 template < > struct _higher_type<double,double> { typedef double type; };
 template < > struct _higher_type<double,long double> { typedef long double type; };
 template < > struct _higher_type<long double,int> { typedef long double type; };
 template < > struct _higher_type<long double,long> { typedef long double type; };
 template < > struct _higher_type<long double,long long> { typedef long double type; };
 template < > struct _higher_type<long double,float> { typedef long double type; };
 template < > struct _higher_type<long double,double> { typedef long double type; };
 template < > struct _higher_type<long double,long double> { typedef long double type; };
 template < typename T1, typename T2 >
 static inline typename _higher_type<T1,T2>::type
 _brian_mod(T1 x, T2 y)
 {{
     return x-y*floor(1.0*x/y);
 }}
 template < typename T1, typename T2 >
 static inline typename _higher_type<T1,T2>::type
 _brian_floordiv(T1 x, T2 y)
 {{
     return floor(1.0*x/y);
 }}
 #ifdef _MSC_VER
 #define _brian_pow(x, y) (pow((double)(x), (y)))
 #else
 #define _brian_pow(x, y) (pow((x), (y)))
 #endif

}

////// HASH DEFINES ///////



void _run_statemonitor_codeobject()
{
	using namespace brian;


	///// CONSTANTS ///////////
	const int _numN = 1;
double* const _array_synapses_w = _dynamic_array_synapses_w.empty()? 0 : &_dynamic_array_synapses_w[0];
const int _num_source_w = _dynamic_array_synapses_w.size();
const int _num_clock_t = 1;
const int _num_indices = 2;
double* const _array_statemonitor_t = _dynamic_array_statemonitor_t.empty()? 0 : &_dynamic_array_statemonitor_t[0];
const int _numt = _dynamic_array_statemonitor_t.size();
	///// POINTERS ////////////
 	
 int32_t*   _ptr_array_statemonitor_N = _array_statemonitor_N;
 double* __restrict  _ptr_array_synapses_w = _array_synapses_w;
 double*   _ptr_array_defaultclock_t = _array_defaultclock_t;
 int32_t* __restrict  _ptr_array_statemonitor__indices = _array_statemonitor__indices;
 double* __restrict  _ptr_array_statemonitor_t = _array_statemonitor_t;


    _dynamic_array_statemonitor_t.push_back(_ptr_array_defaultclock_t[0]);

    const int _new_size = _dynamic_array_statemonitor_t.size();
    // Resize the dynamic arrays
    _dynamic_array_statemonitor_w.resize(_new_size, _num_indices);

    // scalar code
    const int _vectorisation_idx = -1;
        


    
    for (int _i = 0; _i < _num_indices; _i++)
    {
        // vector code
        const int _idx = _ptr_array_statemonitor__indices[_i];
        const int _vectorisation_idx = _idx;
                                        
                    const double _source_w = _ptr_array_synapses_w[_idx];
                    const double _to_record_w = _source_w;



            _dynamic_array_statemonitor_w(_new_size-1, _i) = _to_record_w;
    }

    _ptr_array_statemonitor_N[0] = _new_size;


}


