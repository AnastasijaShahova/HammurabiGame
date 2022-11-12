#ifndef Random_h
#define Random_h
#include <random>
#include <set>
#include <algorithm>

template<typename T>
class Random
{
private:
    T low_;
    T high_;
    std::uniform_int_distribution<> dist_;
public:
    Random(T low, T high) : low_(low), high_(high), dist_(low, high){}
    float RealDistribution()
    {
        static std::mt19937 e;
        std::uniform_real_distribution<float> e1(low_, high_);
        std::random_device rd;
        e.seed(rd());
        return e1(rd);
    }
    int Mt19937()
    {
        static std::mt19937 e;
        std::random_device rd;
        e.seed(rd());
        return dist_(e);
    }
    
    int rand()
    {
        return rand() % high_ + low_;
    }
};

class Distribution
{
public:
    Distribution(){}
    Random<int> random(int low, int high)
    {
        Random rnd(low, high);
        return rnd;
    }

    Random<float> random(float low, float high)
    {
        Random rnd(low, high);
        return rnd;
    }
};

#endif /* Random_h */
