function gradient (num)
clc;
close all;
hold on
syms dzdx(X,Y,a);
syms dzdy(X,Y,a);
syms myGradient(X,Y,a);
syms Z(X,Y,a);

%������� 1: f1(x)=100*(x2-x1^2)^2+5*(1-x1)^2
%������� 2: f2(x)=(x1^2+x2-11)^2+(x1+x2^2-7)^2
% ����� �1=�, �2=�, f1=z
%   ����������� �������: ������������������ ������� �������

switch num
    case 1
        
        Z=100*((Y-X.^2).^2)+5*((1-X).^2)
        dzdx=diff(Z,X);
        dzdy=diff(Z,Y);
        myGradient =[dzdx,dzdy]
        
        [x,y]=meshgrid(-5:0.05:5, -4:0.5:4);
        z=100*((y-x.^2).^2)+5*((1-x).^2);
        
        doGradient([4,0], Z, myGradient);
        
    case 2
        
        Z=(X.^2+Y-11).^2+(X+Y.^2-7).^2
        dzdx=diff(Z,X);
        dzdy=diff(Z,Y);
        myGradient =[dzdx,dzdy]
        
        [x,y]=meshgrid(-7:0.05:7, -7:0.05:7);
        z=(x.^2+y-11).^2+(x+y.^2-7).^2;
        
        doGradient([2,2],Z, myGradient);
        doGradient([-2,-2],Z, myGradient);
        doGradient([2,-2],Z, myGradient);
        doGradient([-2,2],Z, myGradient);
        
end
hS=mesh(x,y,z);
xlabel('x');
ylabel('y');
zlabel('z');

end
function  doGradient( previousDot, Z, myGradient )
%���������� ������������ ������ � ���������� ����
%   ����������� �������: ������������������ ������� �������

syms linkA(a);
syms X(a);
syms Y(a);
syms dot(a);
syms Za(a);
syms functionNorma(X,Y);

% ����������� ���������

syms a;
a=a;
% �����������. ��������! Ÿ �������� ������ ���� � ��������� (0,1).
epsilon = 0.05;
epsilon2 =0.0001;

%������ ���
X=previousDot(1);
Y=previousDot(2); %���������� ��� ���������� ���������

dot = previousDot-a*(eval(myGradient));
X=dot(1);
Y=dot(2);

% ����� eval(Z) - �-��� ��������� ������ �� �
% �a���� ������ ���������� �����������: ���� ����� � ��� �������
%Z ����������
Za=eval(Z);

linkA=a; %��������� ������ � ������, ����� ����� ������ ������ ����������� �

a=OneDimOptimization(Za);

previousDot=eval(dot);

X=previousDot(1);
Y=previousDot(2);

%����� � � Y ��� ����� ��������� ��������, ������ ����� ����� � ����
%� ����� �������� ����������� �������

functionNorma=sqrt((myGradient(1))^2 + (myGradient(2))^2);
prevZa=Za+100;
i=0;
while (eval(functionNorma)>=epsilon) %&& abs(Za-prevZa) >=epsilon2
    i=i+1;
    prevZa=eval(Z); %��� �����
    a=linkA; %����� ������
    
    dot = previousDot-a*(eval(myGradient));
    X=dot(1);
    Y=dot(2);
    Za=eval(Z); %������a� �
    
    a=OneDimOptimization(Za);%������ �������� ������
    X=eval(X);
    Y=eval(Y);
    Za=eval(Z); % ����a
    
    previousDot=eval(dot);
    X=previousDot(1);
    Y=previousDot(2);
    
    
end
i
%  �����
X=[X]
Y=[Y]
Z=[eval(Z)]

plot3 (X,Y,Z,'*k');

end

function minDot = OneDimOptimization (Za)

% ����� ���������� ����������� ���� ������� ����� ��������,�.�. a ��� Z(a)
% ������� �������
e=0; %�������� �������� � �� �, �� � - �������� ���������� �������
b=5;
epsilon=0.00001;
i=1;

flag=0;
while (b-e)/2 >= epsilon
    %flag=0 - ��������� ��� ��������
    %flag=1 - ��������� �
    %flag=2 - ��������� d
    switch flag
        case 0
            c=((3-sqrt(5))/2)*(b-e)+e;
            d=((sqrt(5)-1)/2)*(b-e)+e;
        case 1
            c=((3-sqrt(5))/2)*(b-e)+e;
        case 2
            d=((sqrt(5)-1)/2)*(b-e)+e;
    end
    
    a=c;
    first=eval(Za);
    a=d;
    second=eval(Za);
    
    if first<=second
        %       e=e;
        b=d;
        d=c;
        flag =1;
    else
        e=c;
        %       b=b;
        c=d;
        flag=2;
    end
    i=i+1;
end

minDot=(e+b)/2;
end

