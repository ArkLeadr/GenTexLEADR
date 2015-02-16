I=imread('wall002_hmap2_512x512.jpg');
Ig = double(rgb2gray(I));

% imshow(Ig / 255.0);
Ig = Ig / 255.0; % (Ig-min(min(Ig)))/((max(max(Ig))-min(min(Ig))));

[dx,dy] = imgradientxy(Ig);

dxx = dx .* dx;
dyy = dy .* dy;
dxy = dx .* dy;

v = zeros(size(dx,1),size(dx,2));

dx = flip(dx)';
dy = flip(dy)';
dxx = flip(dxx)';
dyy = flip(dyy)';
dxy = flip(dxy)';
Ig = flip(Ig)';
v = v';

dx = dx(:);
dy = dy(:);
dxx = dxx(:);
dyy = dyy(:);
dxy = dxy(:);
Ig = Ig(:);
v = v(:);


t1 = reshape([dx dy dxx dyy]',4*size(dx,1), []);
t2 = reshape([dxy Ig v v]',4*size(dx,1), []);

tex1 = fopen('tex1','w');
fwrite(tex1,size(I,1),'int32');
fwrite(tex1,size(I,2),'int32');
fwrite(tex1, t1, 'float32');

tex2 = fopen('tex2','w');
fwrite(tex2,size(I,1),'int32');
fwrite(tex2,size(I,2),'int32');
fwrite(tex2,t2,'float32');

fclose(tex1);
fclose(tex2);


