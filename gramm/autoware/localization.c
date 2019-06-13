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

Node computeHessian_cpu5(C=0, TAG=GPU,tra="lll");

Node cc(C=0, TAG=GPU,tra="lll");
Node aa(C=0, TAG=GPU,tra="lll");
Node bb(C=0, TAG=GPU,tra="lll");
sGraph computeHessian;
computeHessian={
  alta(computeHessian_gpu,computeHessian_cpu5);
};

Node matrixSum_gpu (C=0, TAG=CPU,tra="lll");
Node matrixSum_cpu (C=0, TAG=CPU,tra="lll");
sGraph matrixSum;
matrixSum={
  alta(matrixSum_gpu,matrixSum_cpu);
};

Node sumScore_cpu (C=0, TAG=CPU,tcpu_synra="lll");
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
Node exit_2(C=0, TAG=CPU,tra="lll");
Node exit_1(C=0, TAG=CPU,tra="lll");

Node cpu_sync_CT_1(C=0, TAG=CPU,tra="lll");

Condition hessian_2, hessian_3, cond;

sGraph computeHessian_2;
copy(computeHessian_2,computeHessian);

sGraph computeDerivative;

computeDerivative={
  cpu_sync_CD_0;
  if (cond) {
  exit_1;
  }
  else{
  computePointGradients;
  if (hessian_2){
    computeHessian;
    cpu_sync_CT_1;
    computeHessian_2;
    
  }
  cpu_sync_CD_1;
  exit_2;
  }
};





generate(computeDerivative,"/tmp/ll.dot");
