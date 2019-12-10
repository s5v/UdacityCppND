#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
  
  int counter = 0;
  for(Model::Node node : this->Nodes()){
    m_Nodes.push_back(Node(counter, this, node));
    counter++;
  }
  CreateNodeToRoadHashmap();
}

void RouteModel::CreateNodeToRoadHashmap(){
  for(const Model::Road &road : Roads()){
    if(road.type != Model::Road::Type::Footway){
      for(int node_idx : Ways()[road.way].nodes){
        if(node_to_road.find(node_idx) == node_to_road.end()){
          node_to_road[node_idx] = std::vector<const Model::Road*> ();
        }//if 
        node_to_road[node_idx].push_back(&road);
      }//for
    }//if
  }//For Loop
  
}//Function Def.
  
RouteModel::Node* RouteModel::Node::FindNeighbor(std::vector<int> node_indices)
{
  RouteModel::Node* closest_node = nullptr;
  
  RouteModel::Node node;
  for(auto node_index: node_indices){
    node = parent_model->SNodes()[node_index];
    if(this->distance(node) != 0 &&
       node.visited == false){
      if(closest_node == nullptr ||
         this->distance(node) < this->distance(*closest_node)){
        closest_node = &parent_model->SNodes()[node_index];
      }
    }
  }
  
  return closest_node;
}

void RouteModel::Node::FindNeighbors()
{
  for(auto &road : parent_model->node_to_road[this->index]){
    RouteModel::Node *new_n = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
    if(new_n != nullptr){
      this->neighbors.emplace_back(new_n);
    }
  }
  
}

RouteModel::Node &RouteModel::FindClosestNode(float x, float y)
{
  Node input;
  input.x = x;
  input.y = y;
  
  float min_d = std::numeric_limits<float>::max();
  float dist ;
  int closest_idx;
  
  for(const Model::Road &road : Roads()){
    if(road.type != Model::Road::Type::Footway){
      for(int node_idx : Ways()[road.way].nodes){
        dist = input.distance(SNodes()[node_idx]);
        if(dist < min_d){
          closest_idx = node_idx;
          min_d = dist;
        }
      }
    }
  }
  
  return SNodes()[closest_idx];
}