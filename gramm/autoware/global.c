Tag CPU, GPU;

Node localization(C=0, TAG=CPU,tra="lll");
Node objectDetection(C=0, TAG=CPU,tra="lll");
Node objectTracking(C=0, TAG=CPU,tra="lll");
Node reprojection(C=0, TAG=CPU,tra="lll");
Node missionPlanning(C=0, TAG=CPU,tra="lll");
Node motionPlanning(C=0, TAG=CPU,tra="lll");
Node pathFollowing(C=0, TAG=CPU,tra="lll");


sGraph LHS;
LHS={
  objectDetection;
  objectTracking;
  reprojection;
};

sGraph RHS;
RHS={
  missionPlanning;
  motionPlanning;

};
sGraph autoware;
autoware={
  localization;
  par(RHS,LHS);
  pathFollowing;
};
generate(autoware,"/tmp/all.dot");
