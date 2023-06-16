// main.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include "vector.h"

struct Point3 
{
    float x = 0.0f, y = 0.0f, z = 0.0f;

    Point3(float scalar)
        :x(scalar), y(scalar), z(scalar) {}

    Point3(float x, float y, float z)
        :x(x),y(y),z(z) {}

    Point3(const Point3& other) 
        :x(other.x), y(other.y), z(other.z) 
    {
        std::cout << "Point3 COPY!\n";
    }

    Point3(Point3&& other) noexcept
        :x(other.x), y(other.y), z(other.z) 
    {
        std::cout << "point3 MOVE!\n";
    }

    Point3& operator=(const Point3& other)
    {
        std::cout << "Point3 COPY!\n";
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Point3& operator=(Point3&& other)
    {
        std::cout << "point3 MOVE!\n";
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    ~Point3()
    {
        std::cout << "Point3 Destroy!\n";
    }

};

template<typename T>
void PrintVector(const vector<T>& vec)
{
    std::cout << "Vector:\n";
    std::cout << vec << std::endl;
}

template<>
void PrintVector(const vector<Point3>& vec)
{
    std::cout << "Vector:\n";
    std::cout << "size : " << vec.size() << std::endl;

    //TODO write iterators
    for (size_t i = 0; i < vec.size(); i++) 
    {
        std::cout << vec[i].x << ", " << vec[i].y << ", " << vec[i].z << std::endl;
    }
    std::cout << "!-----------------------------------------------!\n";
}


int main()
{
    std::cout << "Hello STL!\n";
    vector<Point3> points;


    points.emplace_back( 40.0f );
    points.PushBack({ 2.0f ,0.1f,0.22f});
    points.PushBack({ 3.0f ,0.6f,0.55f });
    //points.emplace_back(2.0f);
    //PrintVector(points);
    //
    //points.PopBack();
    //points.PopBack();
    //PrintVector(points);
    //points.PopBack();

    //PrintVector(points);
    //points.PopBack();
    //PrintVector(points);
    //points.PushBack({ 2 });

    PrintVector(points);
}
