//
// Created by 罗威 on 2020/12/18.
//

#ifndef INC_20201218_PERSON_H
#define INC_20201218_PERSON_H

//行人
class Person {
private:
    int personIndex;    //行人编号
    double x;           //x坐标
    double y;           //y坐标
    vector<int> storeBelonged; //该行人属于哪些商店范围内
public:
    //构造函数
    Person(int indexNum ,double initX,double initY){
        personIndex = indexNum;
        x = initX;
        y = initY;
    };

    //返回x坐标
    double returnPersonX() const{
        return x;
    }

    //返回y坐标
    double returnPersonY() const{
        return y;
    }

    //添加某个商店到该行人所属商店向量里
    void addStoreBelonged(int storeIndex){
        storeBelonged.push_back(storeIndex);
    }

    //清空向量
    void clearStoreBelonged(){
        storeBelonged.clear();
    }

    //行人移动后，重新设置坐标
    void setPersonNewPosition(double newX,double newY){
        x = newX;
        x = newY;
    }

    //返回行人的编号
    int returnPersonIndex() const{
        return personIndex;
    }


    void printStoreBelonged(){
        cout<<"该行人处在"<<storeBelonged.size()<<"个商店范围内，这些商店的序号如下："<<endl;
        for(int i : storeBelonged){
            cout<< i<<", ";
        }
    }

    vector<int>& returnStoreBelonged(){
        return storeBelonged;
    }

    //该行人是否在某个商店范围内
    bool isInStore(int storeIndex){
        auto findStore = find(storeBelonged.begin(),storeBelonged.end(),storeIndex);
        if(findStore==storeBelonged.end()){
            return false;
        }else{
            return true;
        }
    }

};


#endif //INC_20201218_PERSON_H
