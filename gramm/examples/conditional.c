Tag CPU, GPU;
Node seq1(C=4, TAG=CPU);
Node p1(C=3,PC=3,TAG=GPU);
Node p2(C=2, TAG=CPU);
Node p6(C=2, TAG=CPU);
Node p7(C=2, TAG=CPU);
Node p3(C=1, TAG=CPU);
Node p4(C=1, TAG=CPU);
Node p5(C=1, TAG=CPU);
Node seq2(C=1, TAG=CPU);


Condition C,B; 

Graph tau(T=50,D=40);

tau={
  seq1;
  if (C){
    p1;
    par(p2,p3);
    p5;
  }
  else {
    if(B){
      p6;
    }
    else {
      p7;
    }
    p4;
  }
  seq2;
};

generate(tau,"/tmp/gr.dot");
