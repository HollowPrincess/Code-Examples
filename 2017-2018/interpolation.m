function interpolation(varargin)
%We search interpolational polinomial in the form of Lagrange
clc;
close all;
format long;
leftEnd=-1;
rightEnd=1;
disp ('function:x*log(x+2)');
chooseFuncForInterpolation(@firstTaskFunc,leftEnd,rightEnd);
figure
disp ('function:|x|*x*log(x+2)');
chooseFuncForInterpolation(@secondTaskFunc,leftEnd,rightEnd);
end
function resultPolinomial=doInterpolation(pointFlag,funcFlag,leftEnd,rightEnd,lastNum)
syms x;
syms resultPolinomial(x);
resultPolinomial=0;
syms nodePolinomial(x); %omega(n+1)
nodePolinomial=1;
syms divider(x);
for omegaCounter=0:lastNum
    nodePolinomial=nodePolinomial*(x-pointFlag(leftEnd,rightEnd,lastNum,omegaCounter));
end
nodePolinomialDerivative=diff(nodePolinomial,x);
for interpolationCounter=0:lastNum
    tmp=nodePolinomialDerivative;
    point = pointFlag(leftEnd,rightEnd,lastNum,interpolationCounter);
    a=x;
    x=point;
    tmp=eval(tmp);
    x=a;
    divider=x-point;
    resultPolinomial=resultPolinomial+(funcFlag(point)./tmp)*(nodePolinomial/divider);
end
%pretty(resultPolinomial)
pretty(expand(vpa(resultPolinomial)))
end
function chooseFuncForInterpolation(funcFlag,leftEnd,rightEnd)
x=leftEnd:0.01:rightEnd;
for lastNum=2:7 % number of last node(point) , if lastNum=3 we have 4 points: x0,x1,x2,x3
    subplot((7-2+1)/2,2,lastNum-1);
    disp('number of Nodes:');
    disp( lastNum );
    plot(x,funcFlag(x),'r');
    hold on;
    disp('Polinomial with equidistant nodes: ');
    equidistantPoly=doInterpolation(@equidistantPoint,funcFlag,leftEnd,rightEnd,lastNum);
    plot(x,eval(equidistantPoly),'b');
    disp('Polinomial with optimal nodes: ');
    optimalPoly=doInterpolation(@optimalPoint,funcFlag,leftEnd,rightEnd,lastNum);
    plot(x,eval(optimalPoly),'K');
    legend('function','equidistantPoly','optimalPoly','Location','SouthEast');
end
end
function funcValue = firstTaskFunc(x)
funcValue=x.*log(x+2);
end
function funcValue=secondTaskFunc(x)
funcValue=abs(x).*firstTaskFunc(x);
end
function newX = equidistantPoint(leftEnd,rightEnd,lastNum,num)
% leftEnd=a=-1
% rightEnd=b=1
newX=leftEnd+num*(rightEnd-leftEnd)/lastNum;
end
function newX = optimalPoint(leftEnd,rightEnd,lastNum,num)
newX=((rightEnd-leftEnd)*cos((2*num+1)/(2*(lastNum+1))*pi)+rightEnd+leftEnd)/2;
end
