tic()
for i=1:1:1000
    temp=chol(A_crt);
end
time=toc();
time/1000