% Funcion de Interpolado

function y = interpolado(x,L)
    y = zeros(1,length(x)*L);
    y(1:L:end) = x;
end