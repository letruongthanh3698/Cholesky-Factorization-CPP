clear all
tic()
error_relative_max=1e-5;

matname="data_5489_217669.txt";
resname="data_90449_4427725.M.result.txt";


matrixfile="dataset/"+matname;
resultfile="result/"+resname;

fres=fopen(resultfile);

res_size=fscanf(fres,"%d",2);
res_element=fscanf(fres,"%d",1);
L_res=fscanf(fres,"%d%d%f",[3,res_element])';
%L_res=sparse(uint64(L(1,:)'+1),uint64(L(2,:)'+1)',L(3,:)');
fclose(fres);


fcrt=fopen(matrixfile);
crt_size=fscanf(fcrt,"%d",2);
crt_element=fscanf(fcrt,"%d",1);
E=fscanf(fcrt,"%d%d%f",[3,crt_element])';
A_crt=sparse(uint64(E(:,1)+1),uint64(E(:,2)+1),E(:,3));
fclose(fcrt);



if ~isequal(crt_size,res_size)
    disp("Result is differrent")
else
    L_crt=chol(A_crt);
    crt=0;
    err_max=0;
    err_min=1;
    err_sum=0;
    err=0;
    err_stat_max=15;
    err_stat=zeros(3,err_stat_max);% (1,:) counter, (2,:) value max, (3,:) value min 
    %val_max=max(Aresval);
    %val_min=min(Aresval);
    err_stat(2,:)=-inf;
    err_stat(3,:)=inf;
    inf_count=0;
    for i=1:1:length(L_res)
        val=L_crt(L_res(i,1)+1,L_res(i,2)+1);
        err=abs((L_res(i,3)-val)/val);
        if err~=inf
            err_max=max(err_max,err);
            err_min=min(err_min,err);
            err_sum=err_sum+err;
        else
            inf_count=inf_count+1;
        end
        pos=fix(-(log10(err)))+1;
        if pos>err_stat_max
            pos=err_stat_max;
        end
        if pos<1
            pos=1;
        end
        err_stat(1,pos)=err_stat(1,pos)+1;
        err_stat(2,pos)=max(err_stat(2,pos),abs(L_res(i,3)));
        err_stat(3,pos)=min(err_stat(3,pos),abs(L_res(i,3)));
        %if abs((L_res(i,3)-val))/val>error_relative_max
        %    crt=1;
        %    break;
        %end
    end
    
    fprintf("Error Statistics:\n");
    fprintf("   Error Max: %e\n",err_max);
    fprintf("   Error Min: %e\n",err_min);
    fprintf("   Error Mean: %e\n\n", err_sum/length(L_res));
    for i=err_stat_max:-1:1
        if i>1
            fprintf("     <%.0e : %9d value, absolute max value: %.4e, absolute min value: %.4e \n",10^-(i-1),err_stat(:,i));
        else
            fprintf("     >%.0e : %9d value, absolute max value: %.4e, absolute min value: %.4e, Infinity error: %d number \n",10^-(i),err_stat(:,i),inf_count);
        end 
    end
    %if crt
    %    disp("Result is differrent")
    %else
    %    disp("Correct!")
    %end
end
toc()