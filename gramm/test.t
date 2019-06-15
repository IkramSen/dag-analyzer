Tag CPU, GPU;
Node dd(C=4);
Node bb(TAG=GPU, BAG=KPU,C=5);
Node cc(TAG=GPU, BAG=KPU,C=6);
Node ff(TAG=GPU, BAG=KPU,C=6);
Condition c;
sGraph g;
Graph k(T=50,D=40,D=30);
g={
 dd;
bb;
};

k={
par(ff,g);
cc;
};

generate(k,"/tmp/gr.dot");
