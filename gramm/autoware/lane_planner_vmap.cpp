Tag CPU;


Node find_prev_lane_1(C=0, TAG=CPU,tra="lll");
Node find_lane_1(C=0, TAG=CPU,tra="lll");
Node is_branching_lane_1(C=0, TAG=CPU,tra="lll");
Condition lane_found_1, prev_lane_found_1;

sGraph is_branching_point;
is_branching_point={
  find_lane_1; 
  if (lane_found_1){
    find_prev_lane_1; 
    if (prev_lane_found_1){
      is_branching_lane_1;
    }
  }
};



Node find_lane_2(C=0, TAG=CPU,tra="lll");

sGraph  find_nearest_point_1;
sGraph  find_nearest_point_7;
Node find_nearest_point_2gpu(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_2(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_3(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_4(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_5(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_6(C=0, TAG=CPU,tra="lll");

find_nearest_point_1={
  par(find_nearest_point_2,find_nearest_point_3,find_nearest_point_4,find_nearest_point_5,find_nearest_point_6);
};

Node cpu_init_1(C=0, TAG=CPU,tra="lll");
Node cpu_closing_1(C=0, TAG=CPU,tra="lll");
Node  compute_direction_angle_1(C=0, TAG=CPU,tra="lll");
Node  compute_direction_angle_2(C=0, TAG=CPU,tra="lll");
Node find_near_points_1(C=0, TAG=CPU,tra="lll");
Node find_end_point_1(C=0, TAG=CPU,tra="lll");


Condition nearest_found_3,lane_found_3,end_point_found;
sGraph  find_departure_point;
find_departure_point={
  cpu_init_1;
  find_nearest_point_1; 
  if (nearest_found_3) {
    find_near_points_1; 
    compute_direction_angle_1;
    find_lane_2;
    if (lane_found_3)
      {
	find_end_point_1; 
	if (end_point_found){
	  compute_direction_angle_2;
	}
      }	
  }
  cpu_closing_1;
};


Node init_cpu(C=0, TAG=CPU,tra="lll");
Node sub_func_1(C=0, TAG=CPU,tra="lll");
Node sub_func_2(C=0, TAG=CPU,tra="lll");
Node is_merging_lane_1(C=0, TAG=CPU,tra="lll");
Condition merged_lane; 

sGraph  find_prev_lane;
find_prev_lane={ 
  init_cpu;
  is_merging_lane_1; 
  if (merged_lane) {
    sub_func_1;	
  } else {
    sub_func_2;
  }
};


Node find_end_point_2(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_2(C=0, TAG=CPU,tra="lll");
Node  compute_direction_angle_3(C=0, TAG=CPU,tra="lll");
Node  compute_direction_angle_4(C=0, TAG=CPU,tra="lll");
Condition nearest_found_2, start_point_found, lane_found_2,prev_lane_found_2,nearest_found_4; 
sGraph  find_arrival_point;
Node cpu_init_2(C=0, TAG=CPU,tra="lll");
Node find_near_points(C=0, TAG=CPU,tra="lll");
Node find_lane_3(C=0, TAG=CPU,tra="lll");
Node find_start_point(C=0, TAG=CPU,tra="lll");
find_arrival_point={
  cpu_init_2;
  find_nearest_point_2; 
  if (nearest_found_4) {
    find_near_points;
    compute_direction_angle_3;
    find_lane_3; 
    if (lane_found_2){ 
      find_prev_lane;
      if (prev_lane_found_2){
	find_start_point;
	if (start_point_found){
	  compute_direction_angle_4; 
	}
      }
    }
  }
};

Node sub_func_3(C=0, TAG=CPU,tra="lll");
Node sub_func_4(C=0, TAG=CPU,tra="lll");
Node is_branching_lane_2(C=0, TAG=CPU,tra="lll");
Node cpu_init_9(C=0, TAG=CPU,tra="lll");
Condition branching_lane;
sGraph  find_next_lane;
find_next_lane={
  cpu_init_9;
  is_branching_lane_2;
  if (branching_lane) {
    sub_func_3;
  }
 else {
  sub_func_4;
 }
};

Node find_end_point_3(C=0, TAG=CPU,tra="lll");
Node find_end_point_4(C=0, TAG=CPU,tra="lll");
Node cpu_init_10(C=0, TAG=CPU,tra="lll");
Node cpu_func(C=0, TAG=CPU,tra="lll");
Node  compute_direction_angle_5(C=0, TAG=CPU,tra="lll");
Condition next_lane_found_6,end_point_found_3;
sGraph  find_next_branching_lane;
find_next_branching_lane=
  {
    cpu_init_10;
    find_end_point_3;
    if (end_point_found_3) { 
      find_end_point_4;
      find_next_lane;
      if (next_lane_found_6){
	compute_direction_angle_5;
      }
    }
  };


Node find_end_point_5(C=0, TAG=CPU,tra="lll");
Node find_end_point_6(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_3(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_4(C=0, TAG=CPU,tra="lll");
Node find_nearest_point_5(C=0, TAG=CPU,tra="lll");
Node find_lane_4(C=0, TAG=CPU,tra="lll");
Node cpu_init_8(C=0, TAG=CPU,tra="lll");
Node is_branching_lane_3(C=0, TAG=CPU,tra="lll");
Node sub_func_12(C=0, TAG=CPU,tra="lll");
Node sub_func_13(C=0, TAG=CPU,tra="lll");
Node compute_direction_angle_6(C=0, TAG=CPU,tra="lll");
Node find_next_branching_lane_11 (C=0, TAG=CPU,tra="lll");
Node find_next_branching_lane_12(C=0, TAG=CPU,tra="lll");
Node exiting_func(C=0, TAG=CPU,tra="lll");
Node find_next_lane_15(C=0, TAG=CPU,tra="lll");

Condition c_1, c_2, c_3, c_4, c_5, c_6, c_7, c_8, c_9, c_10, c_11, distance_condition;
sGraph create_fine_vmap;

sGraph    find_arrival_point_8;
copy(find_arrival_point_8,find_arrival_point);

create_fine_vmap={
  cpu_init_8; 
  if (c_1){
    find_nearest_point_3;
  }
  else {
    find_departure_point;
  }
  if (c_2){
    if (c_3){
      find_nearest_point_4; 
    }
    else {
      find_arrival_point_8;
    }
  }
  if (c_4) { 
    find_lane_4; 
    if (c_5){
      sub_func_1;
      find_end_point_5;
      if (c_6)
	{
	  cpu_func ;
	  is_branching_lane_3;
	  if (c_7) {
	    find_end_point_6; 
	    if (c_8){
	      find_nearest_point_5; 
	      if (c_9){
		sub_func_13; 
		if (distance_condition){
		  compute_direction_angle_6; 
		  if (c_10) {
		    find_next_branching_lane_11; 
		  }
		}
		else {
		  find_next_branching_lane_12;
		}
	      }
	      else {
		find_next_lane_15;
	      }
	      if (c_11){ 
		sub_func_12;
	      }
	      exiting_func;
	    }
	  }
	  
	}
    }
  }
}; 


generate(create_fine_vmap,"/tmp/dd.dot");
