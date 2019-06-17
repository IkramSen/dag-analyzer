Tag CPU, GPU;
Node seq1(C=4, TAG=CPU);
Node p1(C=3,PC=3,TAG=GPU);
Node p2(C=2, TAG=CPU);
Node p3(C=1, TAG=CPU);

Node seq2(C=1, TAG=CPU);

sGraph s1, s2, s3;

s1={
  p1;
  par(p2,p3);
};

copy(s1,s2);
copy(s1,s3);
Graph tau(T=50,D=40);

tau={
  seq1;
  par(s1,s2,s3);
  seq2;
};

generate(tau,"/tmp/gr.dot");
