//
// Created by 罗威 on 2020/12/18.
//

#ifndef INC_20201218_STORE_H
#define INC_20201218_STORE_H


//定义商店类
class Store{
private:
    int storeIndex;
    double  x;
    double y;
    vector<int> peopleInScope; //每个商店维护一个向量，存有在商店辐射范围内的所有行人
public:
    Store(int indexNum,double initX,double initY){
        storeIndex = indexNum;
        x = initX;
        y=  initY;
    }

    double returnStoreX() const{
        return x;
    }
    double returnStoreY() const{
        return y;
    }

    int returnStoreIndex() const{
        return storeIndex;
    }

    //
    void addPersonToScope(int personIndex){
        peopleInScope.push_back(personIndex);
    }

    void delPersonFromScope(int personIndex){
        vector<int>::iterator p;
        for(p=peopleInScope.begin();p!=peopleInScope.end();++p){
            if(*p == personIndex){
                peopleInScope.erase(p);//当p是peopleInScope最后一个元素时，删除掉它导致无法跳出for循环
                return;
            }
        }
    }

    vector<int> returnPeopleInScope() const{
        return peopleInScope;
    }

    void printPeopleInScope(){
        cout<<"该商店范围内有"<<peopleInScope.size()<<"个行人，这些行人的序号如下："<<endl;
        vector<int>::iterator p;
        for(p=peopleInScope.begin();p!=peopleInScope.end();++p){
            cout<<*p<<", ";
        }
    }
};


#endif //INC_20201218_STORE_H
