%% PRACTICA 2
%
%   Alejandro Manuel López Gómez
%   Emilio Kenji Hernández Kuramata
%

% fc diezmado 1/2M
% fc interpolado 1/2L
% Primero interpolador luego diezmador

%% LIMPIEZA

clear all;
close all;

%% DIEZMADO POR UN FACTOR ENTERO
%% APARTADO A

[x_n,fs] = audioread("PDS_P2_3A_LE1_G4.wav");
% sound(x_n,fs);

%% APARTADO B

t_x = linspace(0,(length(x_n)-1)/fs,length(x_n));

figure;
plot(t_x,x_n,'red');
title('SEÑAL x(t)');
xlabel('TIEMPO (s)');

%% APARTADO C

lvl = 0.01;
pos = find(abs(x_n) > 0.01);
y_n = x_n(pos(1):pos(end));

%% APARTADO D
%% APARTADO E

M = 2;
g_n = diezmado(y_n,M);

%% APARTADO F

t_y = linspace(0,(length(y_n)-1)/fs,length(y_n));
t_g = t_y(1:M:end);

T_g = t_g(2) - t_g(1);
fs2 = 1/T_g;

%% APARTADO G

figure;
hold on;
plot(t_y,y_n,'x-');
plot(t_g,g_n,'o-');
title("ANTES Y DESPUÉS DIEZMADO");
xlabel("TIEMPO (s)");
xlim([2.01 2.0101]);
legend('y_n','g_n');

%% APARTADO H

f_y = linspace(-fs/2, fs/2, length(y_n));
Y = fftshift(fs*fft(y_n, length(y_n))./length(y_n));

f_g = linspace(-fs/(2*M), fs/(2*M), length(g_n));
G = fftshift((fs/M)*fft(g_n, length(g_n))./length(g_n));

figure;
hold on;
plot(f_y,abs(Y));
plot(f_g,abs(G));
title("ANTES Y DESPUÉS DIEZMADO");
xlabel("FRECUENCIA (Hz)");
legend('Y','G');


%% APARTADO I

% Aliasing, emplear un filtro anti aliasing


%% INTERPOLACIÓN POR UN FACTOR ENTERO
%% APARTADO A
%% APARTADO B

L = 2;
h_n_interpolado = interpolado(y_n,L);

%% APARTADO C

fs_tras_interpolado = fs*L;

%% APARTADO D

G = L;
fc = fs*(1/(2*L));
k_n = Filtro(h_n_interpolado,fs_tras_interpolado,G,fc);

%% APARTADO E

%Ganancia del filtro debe ser L


%% APARTADO F

offset = zeros(1,20);
y_desp = [offset y_n'];

%y_desp(1:6) = [];

t_y = linspace(0,(length(y_desp)-1)/fs,length(y_desp));
t_k = (0:(length(k_n)-1))/(fs*L);

figure;
hold on;
plot(t_y,y_desp,'x-');
plot(t_k,k_n,'o-');
title("ANTES Y DESPUÉS INTERPOLADO");
xlabel("TIEMPO (s)");
xlim([2.01 2.0101]);
legend('y_n','k_n');

%% APARTADO G

f_y = linspace(-fs/2, fs/2, length(y_n))/fs;
Y = fftshift(fs*fft(y_n, length(y_n))./length(y_n));

f_k = linspace(-fs/2, fs/2, length(k_n))/fs;
K = fftshift((fs*L)*fft(k_n, length(k_n))./length(k_n));

figure;
hold on;
plot(f_y,20*log10(abs(Y)));
plot(f_k,20*log10(abs(K)));
title("ANTES Y DESPUÉS INTERPOLADO");
xlabel("FRECUENCIA (Hz)");
legend('Y','K');


%% APARTADO H


%% APARTADO I



%% CAMBIO DE LA FRECUENCIA DE MUESTREO POR UN FACTOR RACIONAL
%% APARTADO A

L = 4;
M = 3;

%% APARTADO B

h_n_interpolado = interpolado(y_n,L);

%% APARTADO C

fs_tras_interpolado = fs*L;

%% APARTADO D

G = L;
fc = fs*(1/(2*L));
k_n = Filtro(h_n_interpolado,fs_tras_interpolado,G,fc);

%% APARTADO E

% G = L;
% fc = fs*(1/(2*L));

%% APARTADO F

g_n = diezmado(k_n,M);

%% APARTADO G

offset = zeros(1,48);
y_desp = [offset y_n'];

t_y = linspace(0,(length(y_desp)-1)/fs,length(y_desp));
t_k = (0:(length(g_n)-1))/(fs*(L/M));

figure;
hold on;
plot(t_y,y_desp,'x-');
plot(t_g,g_n,'o-');
title("ANTES Y DESPUÉS INTERPOLADO");
xlabel("TIEMPO (s)");
xlim([2.01 2.012]);
legend('y_n','k_n');

%% APARTADO H


