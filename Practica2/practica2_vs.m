%% DIEZMADO

[x_n,fs] = audioread("PDS_P2_3A_LE1_G4.wav");
% sound(x_n,fs);
% La frecuencia de muestreo es dada por la funcion audioread

t_x = linspace(0,(length(x_n)-1)/fs,length(x_n));

figure;
plot(t_x,x_n);
xlabel('TIEMPO (s)');
title('SEÑAL x(t)');

lvl = 0.01;
pos = find(abs(x_n) > 0.01);
y_n = x_n(pos(1):pos(end));

% La frecuencia de muestreo no cambia al eliminar muestras, pues el espacio
% entre las mismas permanece constante. Solo se ha eliminado los periodos
% de silencio del principio y final de la señal.

M = 2;

g_n = diezmado(y_n,M);

t_y = linspace(0,(length(y_n)-1)/fs,length(y_n));
t_g = t_y(1:M:end);

% El diezmado toma de la señal original cada M muestras, por tanto en la
% señal a la salida del diezmador la señal en el dominio del tiempo habrá
% encogido por un factor 1/M, sinónimo de que en el dominio de la frecuencia esta se ha
% ensanchado por un factor M.

figure;
hold on;
plot(t_y,y_n,'x-');
plot(t_g,g_n,'o-');
title("ANTES Y DESPUÉS DIEZMADO");
xlabel("TIEMPO (s)");
xlim([2.01 2.011]);
legend('y_n','g_n');

f_y = linspace(-fs/2, fs/2, length(y_n));
Y = fftshift(fs*fft(y_n, length(y_n))./length(y_n));

% f_g = linspace(-fs/(2*M), fs/(2*M), length(g_n));
f_g = linspace(-fs*M/2, fs*M/2, length(g_n));
G = fftshift((fs/M)*fft(g_n, length(g_n))./length(g_n));

figure;
hold on;
plot(f_y,abs(Y));
plot(f_g,abs(G));
title("ANTES Y DESPUÉS DIEZMADO");
xlabel("FRECUENCIA (Hz)");
legend('Y','G');

% En frecuencia se puede ver como ha disminuido la amplitud de la señal por
% un factor 1/M

%% INTERPOLACIÓN

[x_n,fs] = audioread("PDS_P2_3A_LE1_G4.wav");

lvl = 0.01;
pos = find(abs(x_n) > 0.01);
y_n = x_n(pos(1):pos(end));

L = 2;
h_n = interpolado(y_n,L);

% La interpolación incluye muestras nuevas. Mete ceros en el vector. Sin
% embargo, esto no afecta a la amplitud de la señal. En el espectro la
% señal se comprime sin variar su amplitud, lo que reduce su potencia y
% provoca pérdida de energía en la señal.

G = L;
fc = fs*(1/(2*L));

k_n = Filtro(h_n, fs, G, fc);

% El periodo fundamental de la señal va de -0.5 a 0.5. Al interpolar este
% periodo se desplaza a -0.5/L hasta 0.5/L, para evitar repeticiones de la
% señal, se filtra este periodo fundamental que ahora se encuentra en 1/2L

t_y = linspace(0,(length(y_n)-1)/fs,length(y_n));
t_k = (0:(length(k_n)-1))/(fs*L);

figure;
hold on;
plot(t_y,y_n,'x-');
plot(t_k,k_n,'o-');
title("ANTES Y DESPUÉS INTERPOLADO");
xlabel("TIEMPO (s)");
xlim([2.01 2.012]);
legend('y_n','k_n');

f_y = linspace(-fs/2, fs/2, length(y_n));
Y = fftshift(fs*fft(y_n, length(y_n))./length(y_n));

f_k = linspace(-fs*L/2, fs*L/2, length(k_n));
K = fftshift((fs*L)*fft(k_n, length(k_n))./length(k_n));

figure;
hold on;
plot(f_y,abs(Y));
plot(f_k,abs(K));
title("ANTES Y DESPUÉS INTERPOLADO");
xlabel("FRECUENCIA (Hz)");
legend('Y','K');

%% CAMBIO FRACCIONARIO

[x_n,fs] = audioread("PDS_P2_3A_LE1_G4.wav");

lvl = 0.01;
pos = find(abs(x_n) > 0.01);
y_n = x_n(pos(1):pos(end));

L = 4;
M = 3;

h_n_frac = interpolado(y_n,L);

G = L;
fc = fs*(1/(2*L));

k_n_frac = Filtro(h_n_frac, fs, G, fc);

g_n_frac = diezmado(k_n_frac,M);

offset = zeros(1,10);
y_desp = [offset y_n'];

t_y = linspace(0,(length(y_desp)-1)/fs,length(y_desp));
t_g = (0:(length(g_n_frac)-1))/(fs*(L/M));

figure;
hold on;
plot(t_y,y_desp,'x-');
plot(t_g,g_n_frac,'o-');
title("ANTES Y DESPUÉS INTERPOLADO Y DIEZMADO");
xlabel("TIEMPO (s)");
xlim([2.01 2.0101]);
legend('y_n','g_n');

f_y = linspace(-fs/2, fs/2, length(y_n));
Y = fftshift(fs*fft(y_n, length(y_n))./length(y_n));

f_g = linspace(-fs*L/(2*M), fs*L/(2*M), length(g_n_frac));
G = fftshift((fs*L/M)*fft(g_n_frac, length(g_n_frac))./length(g_n_frac));

figure;
hold on;
plot(f_y,abs(Y));
plot(f_g,abs(G));
title("ANTES Y DESPUÉS DIEZMADO");
xlabel("FRECUENCIA (Hz)");
legend('Y','G');









