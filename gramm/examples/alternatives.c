Tag CPU, GPU;
Node seq1(C=4, TAG=CPU);
Node p1(C=4,PC=3,TAG=GPU);
Node p2(C=2, TAG=CPU);
Node seq2(C=1, TAG=CPU);

Graph tau(T=50,D=40);
tau={
  seq1;
  alta(p1,p2);
  seq2;
};

generate(tau,"/tmp/gr.dot");
