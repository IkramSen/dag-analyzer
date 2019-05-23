Tag CPU, GPU;


Node computeExCovX_gpu(C=0, TAG=CPU,tra="lll");
Node computeExCovX_cpu(C=0, TAG=CPU,tra="lll");
sGraph computeExCovX;
computeExCovX={
  alta(computeExCovX_gpu,computeExCovX_cpu);
};

Node computeCovDxdPi_cpu(C=0, TAG=CPU,tra="lll");
Node computeCovDxdPi_gpu(C=0, TAG=CPU,tra="lll");
sGraph computeCovDxdPi;
computeCovDxdPi={
  alta(computeCovDxdPi_gpu,computeCovDxdPi_cpu);
};

Node computeScoreList_cpu(C=0, TAG=CPU,tra="lll");
Node computeScoreList_gpu(C=0, TAG=CPU,tra="lll");
sGraph computeScoreList;
computeScoreList={
  alta(computeScoreList_cpu,computeScoreList_gpu);
};

Node computeScoreGradientList_gpu (C=0, TAG=CPU,tra="lll");
Node computeScoreGradientList_cpu (C=0, TAG=CPU,tra="lll");
sGraph computeScoreGradientList;
computeScoreGradientList={
  alta(computeScoreGradientList_cpu,computeScoreGradientList_gpu);
};


Node computeHessianListS0_gpu (C=0, TAG=GPU,tra="lll");
Node computeHessianListS0_cpu (C=0, TAG=CPU,tra="lll");
sGraph computeHessianListS0;
computeHessianListS0={
  alta(computeHessianListS0_cpu,computeHessianListS0_gpu);
};


Node computePointGradients_cpu(C=0, TAG=CPU,tra="lll");
Node computePointGradients_gpu(C=0, TAG=CPU,tra="lll");
sGraph computePointGradients;
computePointGradients={
  alta(computePointGradients_cpu, computePointGradients_gpu);
};


Node computeHessian_gpu (C=0, TAG=GPU,tra="lll");
Node computeHessian_cpu (C=0, TAG=GPU,tra="lll");
sGraph computeHessian;
computeHessian={
  alta(computeHessian_gpu,computeHessian_cpu);
};

Node matrixSum_gpu (C=0, TAG=CPU,tra="lll");
Node matrixSum_cpu (C=0, TAG=CPU,tra="lll");
sGraph matrixSum;
matrixSum={
  alta(matrixSum_gpu,matrixSum_cpu);
};

Node sumScore_cpu (C=0, TAG=CPU,tra="lll");
Node sumScore_gpu (C=0, TAG=CPU,tra="lll");
sGraph sumScore;
sumScore={
  alta(sumScore_gpu,sumScore_cpu);
};

Node cpu_sync_CD_0(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_1(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_2(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_3(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_4(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_5(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_6(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_7(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_8(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_9(C=0, TAG=CPU,tra="lll");
Node cpu_sync_CD_10(C=0, TAG=CPU,tra="lll");

sGraph computeHessian_2;
Condition hessian_2;
copy(computeHessian_2,computeHessian);


sGraph computeDerivative;
computeDerivative={
  cpu_sync_CD_0;
  computePointGradients;
  if (hessian_2){
    computeHessian;
    cpu_sync_CD_10;
    computeHessian_2;
    
  }
  cpu_sync_CD_1;
  computeExCovX;
  cpu_sync_CD_2;
  computeScoreList;
  cpu_sync_CD_3;
  computeCovDxdPi;
  cpu_sync_CD_4;
  computeScoreGradientList; 
  cpu_sync_CD_5;												
  if (compute_hessian) {
    cpu_sync_CD_6;
    computeHessianListS0;
  }
  cpu_sync_CD_7;
  matrixSum;
  cpu_sync_CD_8;
  sumScore;
  cpu_sync_CD_9;
};

generate(computeDerivative,"/tmp/ll.dot");



Node   cpu_sync_CST_0 (C=0, TAG=CPU,tra="lll");
Node   cpu_sync_CST_1 (C=0, TAG=CPU,tra="lll");
Node   cpu_sync_CST_2 (C=0, TAG=CPU,tra="lll");
Node   cpu_sync_CST_3 (C=0, TAG=CPU,tra="lll");
Node   cpu_sync_CST_4 (C=0, TAG=CPU,tra="lll");

sGraph computeStepMT_cpu;
sGraph computeDerivative_1,computeDerivative_2;
copy(computeDerivative_1,computeDerivative);
copy(computeDerivative_2,computeDerivative);


Node transformPointCloud_cpu_3(C=0, TAG=CPU,tra="lll");
Node transformPointCloud_cpu_4(C=0, TAG=CPU,tra="lll");

computeStepMT_cpu={
  cpu_sync_CST_0;
  transformPointCloud_cpu_3;
  cpu_sync_CST_1;
  computeDerivative_1; 
  cpu_sync_CST_2;
  transformPointCloud_cpu_4; 
  cpu_sync_CST_3;
  computeDerivative_2;
  if (step_iterations) {
   computeHessian_cpu;
  }
  cpu_sync_CST_4;
};


sGraph computeDerivative_3,computeDerivative_4;
copy(computeDerivative_3,computeDerivative);
copy(computeDerivative_4,computeDerivative);

Node   cpu_sync_CST_0_1 (C=0, TAG=CPU,tra="lll");
Node   cpu_sync_CST_1_1 (C=0, TAG=CPU,tra="lll");
Node   cpu_sync_CST_2_1 (C=0, TAG=CPU,tra="lll");
Node   cpu_sync_CST_3_1 (C=0, TAG=CPU,tra="lll");
Node   cpu_sync_CST_4_1 (C=0, TAG=CPU,tra="lll");
Node computeHessian_gpu_1 (C=0, TAG=CPU,tra="lll");
Node transformPointCloud_gpu_3 (C=0, TAG=CPU,tra="lll");
Node transformPointCloud_gpu_4 (C=0, TAG=CPU,tra="lll");
Condition step_iterations_1;

sGraph computeStepMT_gpu;
computeStepMT_gpu={
  cpu_sync_CST_0_1;
  transformPointCloud_gpu_3;
  cpu_sync_CST_1_1;
  computeDerivative_3; 
  cpu_sync_CST_2_1;
  transformPointCloud_gpu_4; 
  cpu_sync_CST_3_1;
  computeDerivative_4;
  if (step_iterations_1) {
   computeHessian_gpu_1;
  }
  cpu_sync_CST_4_1;
};

sGraph computeStepMT;
computeStepMT={
  alta(computeStepMT_cpu,computeStepMT_gpu);
};


Node cpu_sync_CT_0 (C=0, TAG=CPU,tra="lll");
Node cpu_sync_CT_1 (C=0, TAG=CPU,tra="lll");
Node cpu_sync_CT_2 (C=0, TAG=CPU,tra="lll");
Condition guessCondition;
Node transformPointCloud_gpu_5 (C=0, TAG=CPU,tra="lll");
sGraph computeDerivative_5;
copy(computeDerivative_5,computeDerivative);
sGraph  computeStepMT_2;
copy(computeStepMT_2,computeStepMT);

sGraph computeTransformation;
computeTransformation={
  cpu_sync_CT_0; 
  if (guessCondition){
    transformPointCloud_gpu_5; 
  }

  cpu_sync_CT_1;
  computeDerivative;
  computeStepMT_2;  
  cpu_sync_CT_2;
};

generate(computeTransformation,"/tmp/td.dot");
