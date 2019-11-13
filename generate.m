% generate bash files

% === params ===
file = 'C:\Users\Addis\Desktop\exec\template.slurm';
out_path = 'C:\Users\Addis\Desktop\exec\';
ind = 1 : 1000;
% ===========

str0 = fileread(file);
for i = 1:numel(ind)
    str = strrep(str0, '@INT@', num2str(ind(i)));
    filewrite([out_path num2str(ind(i)) '.slurm'], str);
end

warning('conver CRLF using "dos2unix *.sh"');
