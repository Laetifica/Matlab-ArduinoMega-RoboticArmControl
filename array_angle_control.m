% serialport and related functions are from:
% https://www.mathworks.com/help/matlab/import_export/read-streaming-data-from-arduino.html

% file I/O is from earlier class code by Dr. Markvicka

clear;
% establish serial connection; replace "COM6" with your com port
% Check device manager for com ports
arduinoObj = serialport("COM6",115200) % deliberately prints connection

% set terminator characters
configureTerminator(arduinoObj,"CR/LF");

% remove lingering data in arduino buffer
flush(arduinoObj);

% set listener function for arduino data
configureCallback(arduinoObj,"terminator",@readData);

% set safe/home position - configure this if needed
homePosition = [000 090 045 020];
position = homePosition;

%%%%%% Import txt file %%%%%%
% NUM_ROWS should equal the number of angle sets (rows) your file contains.
NUM_ROWS = 3; % CONFIGURE THIS TO MATCH YOUR INPUT FILE
fileID = fopen('angleData.txt');
A = fscanf(fileID,'%f');
A = reshape(A,[4, NUM_ROWS])'  % 4 angles per row, NUM_ROWS rows



%  transmit angle info for each row
for i = 1:size(A,1)
    position = A(i,:) % grab angles
    pause(3);
    % turn position array into string
    sendString = encodeString(position);
    arduinoObj.writeline(sendString);
end


%% function that reads data from arduino when available
function readData(src, ~)

    % Read the ASCII data from the serialport object to console.
    data = readline(src);
    disp(data);


end

%% function to encode angle array into transmission string
function [sendString] = encodeString(position)

    % grab a 3-digit number padded with zeroes on the left from each entry
    % in position, and turn it into a 3-character string. Then concatenate
    % the strings and return as sendstring.

    % *Note* this function works fine when negative angles are only two
    % digits, but may behave erratically when negative 3-digit numbers are
    % used. Needs testing/upgrade of printf format string (e.g. '%03i').
    % I suspect this script may need rework to take 4 digits for each angle. 
    % A better solution would be to process angles to pulselengths in matlab?
    
    J0 = num2str(position(1), '%03i');
    J1 = num2str(position(2), '%03i');
    J2 = num2str(position(3), '%03i');
    EE = num2str(position(4), '%03i');
    sendString = append(J0,J1,J2,EE);

end
