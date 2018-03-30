function nelderMead (num)
clc;
close all;
hold on
syms Z(X,Y);
format long;
%Функция 1: f1(x)=100*(x2-x1^2)^2+5*(1-x1)^2
%Функция 2: f2(x)=(x1^2+x2-11)^2+(x1+x2^2-7)^2
% Пусть х1=х, х2=у, f1=z

switch num
    case 1
        
        Z=100*((Y-X.^2).^2)+5*((1-X).^2)
        
        [x,y]=meshgrid(-5:0.05:5, -4:0.5:4);
        z=100*((y-x.^2).^2)+5*((1-x).^2);
        
        doNM([10, 10, 21, 100 ;...
              9,  -2, 1,  100   ], Z);
        
    case 2
        
        Z=(X.^2+Y-11).^2+(X+Y.^2-7).^2      
                
        [x,y]=meshgrid(-7:0.05:7, -7:0.05:7);
        z=(x.^2+y-11).^2+(x+y.^2-7).^2;
        
        doNM([20, 20, -20, -20 ;...
              20, -20, 20,  -20   ], Z);                
end
hS=mesh(x,y,z);
xlabel('x');
ylabel('y');
zlabel('z');

end
function  doNM( symplex, Z)
%В данной программе симплекс из себя представляет матрицу 3*4 где первая строка координата Х,
%вторая Y, третья - значения функций для точек симплекса
counter=0;
syms functionNorma(X,Y);
% Необходимые константы
% Погрешность. Внимание! Её значения должны быть в интервале (0,1).
epsilon = 0.000000001;
alpha=1; %отражение
beta=0.5; %сжатие 
gamma=2; %растяжение
%вычисляем значение функции
for i=1:4
    X=symplex(1,i);
    Y=symplex(2,i);
    symplex(3,i)=eval(Z);
end
measureOfSpreadFlag=false;
for i=1:3		
			if abs(symplex(3,i)-symplex(3,i+1))>epsilon
				measureOfSpreadFlag=true;
                break;
            end	
end

while measureOfSpreadFlag
    counter=counter+1;
%сортируем
flag=true;
while flag
    flag=false;
    for col=1:3
        if symplex(3,col)>symplex(3,col+1)
            for row=1:3
            symplex(row,col)= symplex(row,col)+ symplex(row,col+1);
            symplex(row,col+1)= symplex(row,col)- symplex(row,col+1);
            symplex(row,col)= symplex(row,col)- symplex(row,col+1);
            end
            flag=true;
        end    
    end
end

%центр тяжести:
center(1)=sum(symplex(1,1:3))/3;
center(2)=sum(symplex(2,1:3))/3;
%отражаем максимальную точку относительно центра тяжести 
new(1)=(1+alpha)*center(1)-alpha*symplex(1,4);
new(2)=(1+alpha)*center(2)-alpha*symplex(2,4);
X=new(1);
Y=new(2);
new(3)=eval(Z);

%Ищем место новой точки в ряду:

%Сравниваем
compressionflag=false; %флаг, который отвечает за сжатие симплекса
if new(3)<symplex(3,1) 
    %Растяжение
    tmp(1)=(1-gamma)*center(1)+gamma*new(1);
    tmp(2)=(1-gamma)*center(2)+gamma*new(2);
    X=tmp(1);
    Y=tmp(2);
    tmp(3)=eval(Z);
    if tmp(3)<new(3)
        for i=1:3
            symplex(i,4)=tmp(i);
        end
    elseif tmp(3)>new(3)
        for i=1:3
            symplex(i,4)=new(i);
        end
    end        
elseif new(3)<symplex(3,3) && new(3)>symplex(3,1) 
    %присвоение 
    for i=1:3
        symplex(i,4)=new(i);
    end
elseif new(3)<symplex(3,4) && new(3)>symplex(3,3) 
    %смена местами и переход на сжатие
     for i=1:3
        symplex(i,4)=new(i);       
     end   
    compressionflag=true;
elseif new(3)>symplex(3,4)
    %переход дальше на сжатие
    compressionflag=true;
end
if compressionflag
    %сжатие
    tmp(1)=beta*symplex(1,4)+(1-beta)*center(1);
    tmp(2)=beta*symplex(2,4)+(1-beta)*center(2);
    X=tmp(1);
    Y=tmp(2);
    tmp(3)=eval(Z);
    if tmp(3)<symplex(3,4)
       for i=1:3
            symplex(i,4)=tmp(i);
       end 
    elseif tmp(3)>symplex(3,4)
       for i=2:4
           symplex(1,i)=0.5*(symplex(1,1)+symplex(1,i));
           symplex(2,i)=0.5*(symplex(2,1)+symplex(2,i));
           X=symplex(1,i);
           Y=symplex(2,i);
           symplex(3,i)=eval(Z);
       end
    end
end
measureOfSpreadFlag=false;
for i=1:3		
			if abs(symplex(3,i)-symplex(3,i+1))>epsilon
				measureOfSpreadFlag=true;
                break;
            end	
end
end
counter
%Чтобы построить точку минимума - возьмем точку симплекса с минимальным
%значением
[Z,index]=min(symplex(3,1:4));
X=symplex(1,index)
Y=symplex(2,index)
Z
%  точка
plot3 (X,Y,Z,'*k');
end