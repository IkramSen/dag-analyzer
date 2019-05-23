Tag CPU;
Node moveConstantTurnRateVelocity(C=0, TAG=CPU,tra="lll");
Node generateYawFromQuaternion(C=0, TAG=CPU,tra="lll");
Node objectsCallback(C=0, TAG=CPU,tra="lll");
Node isObjectValid(C=0, TAG=CPU,tra="lll");
Node  makePrediction(C=0, TAG=CPU,tra="lll");
Node cpu_init_1(C=0, TAG=CPU,tra="lll");
Node init_cpu_1(C=0, TAG=CPU,tra="lll");
Node closing_cpu_2(C=0, TAG=CPU,tra="lll");
sGraph objectsCallback;
objectsCallback={
  init_cpu_1;
  isObjectValid;
  if (valid)
    {
      makePrediction; 
    }
  closing_cpu_2;
};

Node moveConstantVelocity(C=0, TAG=CPU,tra="lll");
Node moveConstantTurnRateVelocity(C=0, TAG=CPU,tra="lll");
Node moveConstantTurnRateVelocity(C=0, TAG=CPU,tra="lll");
sGraph generatePredictedObject;
Condition condition_1, condition_2;
generatePredictedObject ={
  cpu_init_1; 
  if (condition_1) {
    moveConstantVelocity;
  }
  else {
    if (condition_2)
      {
	moveConstantTurnRateVelocity; 
      }
  }
};

generate(generatePredictedObject,"/tmp/object.dot");
generate(objectsCallback,"/tmp/callobject.dot");
