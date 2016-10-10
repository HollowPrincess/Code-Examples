function  WordClickNone( varargin )
global COUNTERTEXTVAR;
global Answer;
global tmpAnswer;
p1=varargin{3};
x=get(p1,'XData');
if isempty(Answer{x})==false
delete (Answer{x}) ;
end
COUNTERTEXTVAR{x}=1;
tmpAnswer{x}={'-'};
end

