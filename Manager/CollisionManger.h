#pragma once
class CollisionManger {
  public:
    CollisionManger(); // 构造函数
    ~CollisionManger(); // 析构函数
    bool CollisionManger::obb(Sprite** sp, Sprite** sp2); // 检查模式obb
    bool CollisionManger::obb(utils::useSpSt st1, utils::useSpSt st2); // 检查模式obb
    bool CollisionManger::aabb(Sprite** sp, Sprite** sp2); // 检查模式aabb 非向量模式
    void CollisionManger::getShapePoints(Sprite** sp, const int num); // 获取形状的点
    void CollisionManger::initVec(); // 将点转化为单位向量
    void CollisionManger::getOneVec(const utils::usePoint& p1, const utils::usePoint& p2, int num);
    bool CollisionManger::getVecProjection(); // 获取向量投影
    bool CollisionManger::comparePoints(const int num); // 对比点的信息判断是否碰撞
    void CollisionManger::getSLCoordinateSystem(Sprite** sp, const int num); // 获取局部坐标系点信息未旋转
    void CollisionManger::getShapePoints(const utils::useSpSt st, const int num); // 以结构的形式获取点信息 方便预判断
    void CollisionManger::getSLCoordinateSystem(const utils::useSpSt st, const int num); // 以结构的形式获取点信息预判断
    void CollisionManger::polarCoordinates(const utils::usePoint& p, float angle, float distance, utils::usePoint& cp); // 极坐标位移
    float CollisionManger::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2); // 获取两点之间的角度
    float CollisionManger::bezierCurve(float p0, float p1, float p2, float t); // 贝塞尔曲线
  private:
    vector<utils::usePoint> vec; // 储存单位向量
    vector<vector<utils::usePoint>> points; // 储存形状点的信息
    vector<utils::usePoint> proPoint; // 投影的信息这里的点是储存的最大值和最小值
  private:
    void CollisionManger::clear(); // 清空所有点的缓存
};
