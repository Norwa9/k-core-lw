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
//        vector<int>::iterator p;
//        for(p=peopleInScope.begin();p!=peopleInScope.end();++p){
//            if(*p == personIndex){
//                peopleInScope.erase(p);
//                return;//当p是peopleInScope最后一个元素时，删除掉它导致无法跳出for循环，所以加一个return避免这种情况。
//            }
//        }
        vector<int>::iterator p;
        for(p=peopleInScope.begin();p!=peopleInScope.end();){
            if(*p==personIndex)
                p=peopleInScope.erase(p);
            else
                ++p;
        }
    }

    vector<int>& returnPeopleInScope() {
        return peopleInScope;
    }

    void printPeopleInScope(){
        cout<<"该商店范围内有"<<peopleInScope.size()<<"个行人，这些行人的序号如下："<<endl;
        vector<int>::iterator p;
        for(p=peopleInScope.begin();p!=peopleInScope.end();++p){
            cout<<*p<<", ";
        }
    }

    bool hasPerson(int personIndex){
        auto isPersonInStore = find(peopleInScope.begin(),peopleInScope.end(),personIndex);
        if(isPersonInStore==peopleInScope.end()){
            return false;
        }else{
            return true;
        }
    }
};


#endif //INC_20201218_STORE_H
