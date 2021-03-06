//
// Created by Dell on 2020/12/16.
//

#include "graph.h"
unordered_map<unsigned int, set<Road> > graph=unordered_map<unsigned int,set<Road>>();

/**
* read road data from text file and build the graph
* @param file_path
* @return
*/
void read_file(string file_path) {

    //read file
    clock_t start = 0, finish = 0;
    start = clock();
    ifstream input_file(file_path.c_str());
    if (!input_file.is_open()) {
        cout << "error opening file" << file_path << endl;
    }
    int buffer_size = 20480;
    char buffer[20480];
    while (input_file.getline(buffer, buffer_size)) {
        string buffer_string = buffer;

        stringstream ss;
        // extract start node ID
        unsigned long start_pos = 0;
        unsigned long end_pos = buffer_string.find(' ', start_pos);
        string start_NID_string = buffer_string.substr(start_pos, end_pos - start_pos);
        ss << start_NID_string;
        unsigned int start_NID;
        ss >> start_NID;


        // extract end node ID
        start_pos = end_pos + 1;
        end_pos = buffer_string.find(' ', start_pos);
        string end_NID_string = buffer_string.substr(start_pos, end_pos - start_pos);
        ss.clear();
        ss << end_NID_string;
        unsigned int end_NID;
        ss >> end_NID;
        //cout<<"end_nid: "<<end_NID<<endl;


        // extract length
        start_pos = end_pos + 1;
        end_pos = buffer_string.find(' ', start_pos);
        string road_length_string = buffer_string.substr(start_pos, end_pos - start_pos);
        ss.clear();
        ss << road_length_string;
        double road_length;
        ss >> road_length;
        //cout<<"road_length: "<<road_length<<endl;


        //cout<<"start: "<<start_NID<<", end: "<<end_NID<<endl;
        Road road(start_NID, end_NID, road_length);
        // find road set according to start node id
        auto iterator1 = graph.find(start_NID);
        if (iterator1 != graph.end()) {
            set<Road> value = iterator1->second;
            value.emplace(road);
            graph[start_NID] = value;
        } else {
            set<Road> value;
            value.insert(road);
            graph[start_NID] = value;
        }

        // find road set according to end node id
        iterator1 = graph.find(end_NID);
        if (iterator1 != graph.end()) {
            set<Road> value = iterator1->second;
            value.emplace(road);
            graph[end_NID] = value;
        } else {
            set<Road> value;
            value.insert(road);
            graph[end_NID] = value;
        }
        //cout<<graph.size()<<endl;
        //cout<<revert_index.size()<<endl;
    }
    input_file.close();
    finish = clock();
    double totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
    cout << "<load file> time consume:" << totaltime << " secondes" << endl;
}
