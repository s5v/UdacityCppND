#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;
  
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);

}

/**
Function Which Does the Actual A Star Search Over here
*/

void RoutePlanner::AStarSearch(void)
{
  
  start_node->visited = true;
  open_list.push_back(start_node);
  
  RouteModel::Node *curr = nullptr;
  
  while(open_list.size() > 0)
  {
    curr = NextNode();
    if(curr->distance(*end_node) == 0)
    {
      m_Model.path = ConstructFinalPath(curr);
      return;
    }//Reached End
    
    AddNeighbors(curr);
    
    
    
  }//While Loop
  return;
  
}//AStarSearch Function Def.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node)
{
 std::vector<RouteModel::Node> path_found;
  distance = 0.0;
  RouteModel::Node parent;
  
  while(current_node->parent != nullptr){
    path_found.push_back(*current_node);
    parent = *(current_node->parent);
    distance += current_node->distance(parent);
    current_node = current_node->parent;
  }
  
  path_found.push_back(*current_node);
  distance *= m_Model.MetricScale();
  return path_found;
  
}

float RoutePlanner::CalculateHValue(RouteModel::Node* n )
{
  return n->distance(*end_node);
}

RouteModel::Node* RoutePlanner::NextNode()
{
  //Sort open_list
  std::sort(open_list.begin(), open_list.end(),
            [](const auto &_1st, const auto &_2nd){
              return _1st->h_value + _1st->g_value <
                _2nd->h_value + _2nd->g_value;});
  
  //Get the First or Last Min Node
  RouteModel::Node *low = open_list.front();
  
  //Delete it from Open List 
  open_list.erase(open_list.begin());
  return low;
    
}

 void RoutePlanner::AddNeighbors(RouteModel::Node* node)
 {
   //populate the Node Neighbor Vector
   node->FindNeighbors();
   
   for(auto n: node->neighbors){
     n->parent = node;
     n->g_value = node->g_value + node->distance(*n);
     n->h_value = CalculateHValue(n);
     open_list.push_back(n);
     n->visited = true;
   }//for loop
   
   return;
   
 }


