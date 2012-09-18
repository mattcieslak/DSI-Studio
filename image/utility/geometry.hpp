//---------------------------------------------------------------------------
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <functional>
#include <numeric>
#include <algorithm>
//---------------------------------------------------------------------------
namespace image
{

template<unsigned int Dim>
class geometry
{
public:
    unsigned int dim[Dim];
public:
    static const unsigned int dimension = Dim;
public:
    geometry(void)
    {
        clear();
    }
    geometry(const geometry<Dim>& rhs)
    {
        *this = rhs;
    }
    template<typename pointer_type>
    explicit geometry(const pointer_type* rhs)
    {
        *this = rhs;
    }
    const geometry<Dim>& operator=(const geometry<Dim>& rhs)
    {
	if(this == &rhs)
            return *this;
        std::copy(rhs.dim,rhs.dim+Dim,dim);
        return *this;
    }
    template<typename pointer_type>
    const geometry<Dim>& operator=(const pointer_type* rhs)
    {
        std::copy(rhs,rhs+Dim,dim);
        return *this;
    }
public:
    unsigned int size(void) const
    {
        unsigned int prod = dim[0];
        for (unsigned int index = 1;index < Dim;++index)
            prod *= dim[index];
        return prod;
    }
    void clear(void)
    {
        std::fill(dim,dim+Dim,0);
    }
    void swap(geometry<Dim>& rhs)
    {
        for (unsigned int index = 1;index < Dim;++index)
            std::swap(dim[index],rhs.dim[index]);
    }
public:
    const unsigned int* begin(void) const
    {
        return dim;
    }
    const unsigned int* end(void) const
    {
        return dim+Dim;
    }
    unsigned int operator[](unsigned int index) const
    {
        return dim[index];
    }
    unsigned int* begin(void)
    {
        return dim;
    }
    unsigned int* end(void)
    {
        return dim+Dim;
    }
    unsigned int& operator[](unsigned int index)
    {
        return dim[index];
    }
public:
    template<typename T>
    bool is_valid(const T& pos) const
    {
        for (unsigned int index = 0;index < Dim;++index)
            if (pos[index] >= 0 || pos[index] < dim[index])
                return false;
        return true;
    }
    template<typename T>
    bool is_edge(const T& pos) const
    {
        for (unsigned int index = 0;index < Dim;++index)
            if (pos[index] == 0 || pos[index]+1 == dim[index])
                return true;
        return false;
    }
public:
    unsigned int width(void) const
    {
        return dim[0];
    }
    unsigned int height(void) const
    {
        return dim[1];
    }
    unsigned int depth(void) const
    {
        return dim[2];
    }
public:
    bool operator==(const geometry<Dim>& rhs) const
    {
        for (unsigned int index = 0;index < Dim;++index)
            if (dim[index] != rhs.dim[index])
                return false;
        return true;
    }
    bool operator!=(const geometry<3>& rhs) const
    {
        return !(*this == rhs);
    }

};



template<>
class geometry<1>
{
    union
    {
        unsigned int dim[1];
        struct
        {
            unsigned int w;
        };
    };
public:
    static const unsigned int dimension = 1;
public:
    geometry(void):w(0) {}
    geometry(unsigned int w_):w(w_) {}

    geometry(const geometry<1>& rhs)
    {
        *this = rhs;
    }
    template<typename pointer_type>
    explicit geometry(const pointer_type* rhs)
    {
        *this = rhs;
    }
    const geometry<1>& operator=(const geometry<1>& rhs)
    {
        w = rhs.w;
        return *this;
    }
    template<typename pointer_type>
    const geometry<1>& operator=(const pointer_type* rhs)
    {
        w = rhs[0];
        return *this;
    }
    const geometry<1>& operator=(const unsigned short* rhs)
    {
        w = rhs[0];
        return *this;
    }
public:
    unsigned int size(void) const
    {
        return w;
    }
    void clear(void)
    {
        w = 0;
    }
    void swap(geometry<1>& rhs)
    {
        std::swap(w,rhs.w);
    }
public:
    const unsigned int* begin(void) const
    {
        return dim;
    }
    const unsigned int* end(void) const
    {
        return dim+1;
    }
    unsigned int operator[](unsigned int index) const
    {
        return dim[index];
    }
    unsigned int* begin(void)
    {
        return dim;
    }
    unsigned int* end(void)
    {
        return dim+1;
    }
    unsigned int& operator[](unsigned int index)
    {
        return dim[index];
    }
public:
    template<typename T>
    bool is_valid(T x) const
    {
        return x >= 0 && x < dim[0];
    }
    template<typename T>
    bool is_edge(T x) const
    {
        return x == 0 || x+1 == dim[0];
    }
    template<typename T>
    bool is_valid(T& pos) const
    {
        return pos[0] >= 0 && pos[0]+1 <= dim[0];
    }
    template<typename T>
    bool is_edge(T& pos) const
    {
        return pos[0] == 0 || pos[0]+1 == dim[0];
    }
public:
    unsigned int width(void) const
    {
        return w;
    }
    unsigned int plane_size(void) const
    {
        return w;
    }
public:
    bool operator==(const geometry<1>& rhs) const
    {
        return dim[0] == rhs.dim[0];
    }
    bool operator!=(const geometry<1>& rhs) const
    {
        return !(*this == rhs);
    }

};

template<>
class geometry<2>
{
    union
    {
        unsigned int dim[2];
        struct
        {
            unsigned int w;
            unsigned int h;
        };
    };
public:
    static const unsigned int dimension = 2;
public:
    geometry(void):w(0),h(0) {}
    geometry(unsigned int w_,unsigned int h_):w(w_),h(h_) {}
    geometry(const geometry<2>& rhs)
    {
        *this = rhs;
    }
    template<typename pointer_type>
    explicit geometry(const pointer_type* rhs)
    {
        *this = rhs;
    }
    const geometry<2>& operator=(const geometry<2>& rhs)
    {
        w = rhs.w;
        h = rhs.h;
        return *this;
    }
    template<typename pointer_type>
    const geometry<2>& operator=(const pointer_type* rhs)
    {
        w = rhs[0];
        h = rhs[1];
        return *this;
    }
public:
    unsigned int size(void) const
    {
        return w*h;
    }
    void clear(void)
    {
        w = h = 0;
    }
    void swap(geometry<2>& rhs)
    {
        std::swap(w,rhs.w);
        std::swap(h,rhs.h);
    }
public:
    const unsigned int* begin(void) const
    {
        return dim;
    }
    const unsigned int* end(void) const
    {
        return dim+2;
    }
    unsigned int operator[](unsigned int index) const
    {
        return dim[index];
    }
    unsigned int* begin(void)
    {
        return dim;
    }
    unsigned int* end(void)
    {
        return dim+2;
    }
    unsigned int& operator[](unsigned int index)
    {
        return dim[index];
    }

public:
    template<typename T>
    bool is_valid(T x,T y) const
    {
        return x >= 0 && y >= 0 && x < dim[0] && y < dim[1];
    }
    template<typename T>
    bool is_edge(T x,T y) const
    {
        return x == 0 || y == 0 || x+1 == dim[0] || y+1 == dim[1];
    }
    template<typename T>
    bool is_valid(const T& pos) const
    {
        return pos[0] >= 0 && pos[1] >= 0 && pos[0]+1 <= dim[0] && pos[1]+1 <= dim[1];
    }
    template<typename T>
    bool is_edge(const T& pos) const
    {
        return pos[0] == 0 || pos[1] == 0 || pos[0]+1 == dim[0] || pos[1]+1 == dim[1];
    }
public:
    unsigned int width(void) const
    {
        return w;
    }
    unsigned int height(void) const
    {
        return h;
    }
    unsigned int plane_size(void) const
    {
        return w*h;
    }
public:
    bool operator==(const geometry<2>& rhs) const
    {
        return dim[0] == rhs.dim[0] && dim[1] == rhs.dim[1];
    }
    bool operator!=(const geometry<2>& rhs) const
    {
        return !(*this == rhs);
    }

};
template<>
class geometry<3>
{
public:
    union
    {
        unsigned int dim[3];
        struct
        {
            unsigned int w;
            unsigned int h;
            unsigned int d;
        };
    };
    mutable unsigned int wh;
    mutable unsigned int size_;
public:
    static const unsigned int dimension = 3;
public:
    geometry(void):w(0),h(0),d(0),wh(0),size_(0) {}
    geometry(unsigned int w_,unsigned int h_,unsigned int d_):w(w_),h(h_),d(d_),wh(0),size_(0) {}
    geometry(const geometry<3>& rhs)
    {
        *this = rhs;
    }
    template<typename pointer_type>
    explicit geometry(const pointer_type* rhs)
    {
        *this = rhs;
    }
    const geometry<3>& operator=(const geometry<3>& rhs)
    {
        w = rhs.w;
        h = rhs.h;
        d = rhs.d;
        wh = rhs.wh;
        size_ = rhs.size_;
        return *this;
    }
    template<typename pointer_type>
    const geometry<3>& operator=(const pointer_type* rhs)
    {
        w = rhs[0];
        h = rhs[1];
        d = rhs[2];
        wh = size_ = 0;
        return *this;
    }
public:
    unsigned int size(void) const
    {
        if(w && !size_)
            size_ = plane_size()*d;
        return size_;
    }
    void clear(void)
    {
        w = h = d = wh = size_ = 0;
    }
    void swap(geometry<3>& rhs)
    {
        std::swap(w,rhs.w);
        std::swap(h,rhs.h);
        std::swap(d,rhs.d);
        std::swap(wh,rhs.wh);
        std::swap(size_,rhs.size_);
    }
public:
    const unsigned int* begin(void) const
    {
        return dim;
    }
    const unsigned int* end(void) const
    {
        return dim+3;
    }
    unsigned int operator[](unsigned int index) const
    {
        return dim[index];
    }
    unsigned int* begin(void)
    {
        wh = size_ = 0;
        return dim;
    }
    unsigned int* end(void)
    {
        wh = size_ = 0;
        return dim+3;
    }
    unsigned int& operator[](unsigned int index)
    {
        wh = size_ = 0;
        return dim[index];
    }

public:
    template<typename T>
    bool is_valid(T x,T y,T z) const
    {
        return x >= 0 && y >= 0 && z >= 0 && x < w && y < h && z < d;
    }
    template<typename T>
    bool is_valid(const T& pos) const
    {
        return pos[0] >= 0 && pos[1] >= 0 && pos[2] >= 0 &&
               pos[0] <= dim[0]-1 && pos[1] <= dim[1]-1 && pos[2] <= dim[2]-1;
    }
    template<typename T>
    bool is_edge(T x,T y,T z) const
    {
        return x == 0 || y == 0 || z == 0 || x+1 == dim[0] || y+1 == dim[1] || z+1 == dim[2];
    }
    template<typename T>
    bool is_edge(const T& pos) const
    {
        return pos[0] == 0 || pos[1] == 0 || pos[2] == 0 ||
               pos[0]+1 == dim[0] || pos[1]+1 == dim[1] || pos[2]+1 == dim[2];
    }
public:
    unsigned int width(void) const
    {
        return w;
    }
    unsigned int height(void) const
    {
        return h;
    }
    unsigned int depth(void) const
    {
        return d;
    }
    unsigned int plane_size(void) const
    {
        if (w && !wh)
            wh = w*h;
        return wh;
    }
public:
    bool operator==(const geometry<3>& rhs) const
    {
        return dim[0] == rhs.dim[0] && dim[1] == rhs.dim[1] && dim[2] == rhs.dim[2];
    }
    bool operator!=(const geometry<3>& rhs) const
    {
        return !(*this == rhs);
    }

};

}
#endif
