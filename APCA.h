//
// Created by zzhfeng on 2018/3/14.
//

#ifndef APCA_PCH_APCA_H
#define APCA_PCH_APCA_H

#pragma once

#include <vector>

/**
 * 数据结构
 */
struct PACA_PCH_DATA{
    int counter;
    float value;
};

/**
 * PACA_PCH类
 */
class PACA_PCH{
private:
    //数据结构
    PACA_PCH_DATA paca_pch_data;
    //数据点集
    std::vector<float> points;
    //允许的偏差值
    float error_tolerance;
    //数据集的最大值
    float max,pre_max;
    //数据集的最小值
    float min,pre_min;

public:
    //构造函数
    PACA_PCH(float e);

    //读取编码数值数量
    int get_width();

    //读取编码后的模拟值
    float get_code_value();

    //编码数值f
    bool push_point(float f);

    //开始编码
    void start(float f);

    //读取本次编码模拟中的所有数据点
    std::vector<float> get_points();

    //重置
    void reset();
};

/**
 * 构造函数
 * @param e
 */
PACA_PCH::PACA_PCH(float e) {
    error_tolerance = e;
}

/**
 * 读取编码数量
 * @return
 */
int PACA_PCH::get_width() {
    return paca_pch_data.counter;
}

/**
 * 读取编码值
 * @return
 */
float PACA_PCH::get_code_value() {
    return paca_pch_data.value;
}

/**
 * 编码新的数据点
 * @param f
 * @return 返回结果为true时表示成功编码
 *          为false时表示该数据点在本段编码中失败，需要重新开始新的编码
 */
bool PACA_PCH::push_point(float f) {
    max = max > f ? max : f;
    min = min < f ? min : f;
    if(max - min <= 2 * error_tolerance) {
        points.push_back(f);
        pre_max = max;
        pre_min = min;
        paca_pch_data.counter += 1;
        return true;
    }
    paca_pch_data.value = (pre_min + pre_max) / 2;
    return false;
}

/**
 * 开始一次新的编码
 * @param f
 */
void PACA_PCH::start(float f) {
    max = pre_max = f;
    min = pre_max = f;
    points.clear();
    points.push_back(f);
    paca_pch_data.counter = 1;
}

/**
 * 读取被编码的数据点
 * @return
 */
std::vector<float> PACA_PCH::get_points() {
    return points;
}

/**
 * 重置
 */
void PACA_PCH::reset() {
    points.clear();
    paca_pch_data.counter = 0;
}

#endif //APCA_PCH_APCA_H
