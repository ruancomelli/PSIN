% %% proccessData.m
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%     INITIALIZE PROGRAM     %%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Initializing Program');

%% inputPath:
clear
inputPath = '../../_output/';                   % Path where to look for input
outputMATLAB = '../../_output/MATLAB_output/';   % Path where to MATLAB must output

disp('Done');

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%     READ DATA     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% ----- Read main output file -----
disp('Reading Main Output File');

fileID = fopen([inputPath, 'output.txt']);
fileCell = textscan(fileID, '%s %f');

tags = fileCell{1};
values = fileCell{2};

% Number of Particles
nParticlesIdx = find( strcmpi(tags, '<nParticles>') );
nParticles = values(nParticlesIdx);

% Initial Instant
initialTimeStepIdx = find( strcmpi(tags, '<initialTime>') );
initialTime = values(initialTimeStepIdx);

% Time Step
timeStepIdx = find( strcmpi(tags, '<timeStep>') );
timeStep = values(timeStepIdx);

% Final Instant
finalTimeIdx = find( strcmpi(tags, '<finalTime>') );
finalTime = values(finalTimeIdx);

% Taylor Order
taylorOrderIdx = find( strcmpi(tags, '<taylorOrder>') );
taylorOrder = values(taylorOrderIdx);

disp('Done')

%% ----- Read particle files -----
disp('Reading Particle Files');

energyIdx = 1;
positionIdx = 2;
velocityIdx = 3;
linearMomentumIdx = 4;
orientationIdx = 5;
rotationalVelocityIdx = 6;
angularMomentumIdx = 7;

numberOfFilesPerParticle = 7;
particleData = cell(nParticles, numberOfFilesPerParticle);
particleFileCell = cell(nParticles, 1);

for counter = 1 : nParticles
    disp(['Particle ', int2str(counter)]);

    particleInputPath = [inputPath, 'Particle', int2str(counter), '/'];
    
    fileID = fopen([particleInputPath, 'data.txt']);
    particleFileCell{counter} = textscan(fileID, '%s %f');
    
    particleData{counter, energyIdx} = csvread([particleInputPath, 'energy.txt']);
    particleData{counter, positionIdx} = csvread([particleInputPath, 'position.txt']);
    particleData{counter, velocityIdx} = csvread([particleInputPath, 'velocity.txt']);
    particleData{counter, linearMomentumIdx} = csvread([particleInputPath, 'linear_momentum.txt']);
    particleData{counter, orientationIdx} = csvread([particleInputPath, 'orientation.txt']);
    particleData{counter, rotationalVelocityIdx} = csvread([particleInputPath, 'rotational_velocity.txt']);
    particleData{counter, angularMomentumIdx} = csvread([particleInputPath, 'angular_momentum.txt']);
end

disp('Done');

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%     PROCCESS DATA     %%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Proccessing Data');

radius = zeros(nParticles, 1);
for counter = 1 : nParticles
    radiusIdx = find( strcmpi(particleFileCell{counter}{1},'<Radius>') );
    radius(counter) = particleFileCell{counter}{2}(radiusIdx);
end

timeVector = initialTime:timeStep:finalTime;
nTimeSteps = length(timeVector);

cmap = colormap( jet(nParticles) );
cmap(2, :) = [1.0, 0.0, 0.0]; % red

%% ----- Plot Energy -----
disp('Plotting Energy');

totalEnergy = zeros(nTimeSteps, 1);

for counter = 1 : nParticles
    totalEnergy = totalEnergy + particleData{counter, energyIdx};
end

fig = figure('Visible', 'off');
    title('Mechanical Energy');
    xlabel('Time [s]');
    ylabel('Mechanical Energy [J]');
    
    hold on
    
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, energyIdx}, ...
            'DisplayName', ['Particle ', int2str(counter)], ...
            'Color', cmap(counter, :));
    end
    plot(timeVector, totalEnergy, 'Color', 'black', ...
        'LineStyle', '-', 'LineWidth', 1.0, ...
        'DisplayName', 'Total Mechanical Energy');
    legend('show');
    
    disp('Saving');
    
    saveas(fig, [outputMATLAB, 'mechanical_energy_plot.png']);  
    hold off  

disp('Done');
    
%% ----- Plot Linear Momentum -----
disp('Plotting Linear Momentum');

totalLinearMomentum = zeros(nTimeSteps, 3);

for counter = 1 : nParticles
    totalLinearMomentum = totalLinearMomentum + particleData{counter, linearMomentumIdx};
end

disp('Plotting X Linear Momentum');

fig = figure('Visible', 'off');
    title('Linear Momentum - X Direction');
    xlabel('Time [s]');
    ylabel('X Linear Momentum [kg*m/s]');
    
    hold on
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, linearMomentumIdx}(:,1), ...
        'DisplayName', ['Particle ', int2str(counter)], ...
        'Color', cmap(counter, :));
    end
    plot(timeVector, totalLinearMomentum(:,1), 'Color', 'black', ...
        'LineStyle', '-', ...
        'LineWidth', 1.0, ...
        'DisplayName', 'Total X Linear Momentum');
    legend('show');
    
    disp('Saving');
    
    saveas(fig, [outputMATLAB, 'X_linear_momentum_plot.png']);    
    hold off  

disp('Plotting Y Linear Momentum');

fig = figure('Visible', 'off');
    title('Linear Momentum - Y Direction');
    xlabel('Time [s]');
    ylabel('Y Linear Momentum [kg*m/s]');
    
    hold on
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, linearMomentumIdx}(:,2), ...
            'DisplayName', ['Particle ', int2str(counter)], ...
            'Color', cmap(counter, :));
    end
    plot(timeVector, totalLinearMomentum(:,2), 'Color', 'black', ...
        'LineStyle', '-', ...
        'LineWidth', 1.0, ...
        'DisplayName', 'Total Y Linear Momentum');
    legend('show');
    
    disp('Saving');
    
    saveas(fig, [outputMATLAB, 'Y_linear_momentum_plot.png']);     
    hold off  

disp('Plotting Z Linear Momentum');

fig = figure('Visible', 'off');
    title('Linear Momentum - Z Direction');
    xlabel('Time [s]');
    ylabel('Z Linear Momentum [kg*m/s]');
    
    hold on
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, linearMomentumIdx}(:,3), ...
            'DisplayName', ['Particle ', int2str(counter)], ...
            'Color', cmap(counter, :));
    end
    plot(timeVector, totalLinearMomentum(:,3), 'Color', 'black', ...
        'LineStyle', '-', ...
        'LineWidth', 1.0, ...
        'DisplayName', 'Total Z Linear Momentum');
    legend('show');
    
    disp('Saving');
    
    saveas(fig, [outputMATLAB, 'Z_linear_momentum_plot.png']);    
    hold off  
    
disp('Done');
    
    
%% ----- Plot Angular Momentum -----
disp('Plotting Angular Momentum');

totalAngularMomentum = zeros(nTimeSteps, 3);

for counter = 1 : nParticles
    totalAngularMomentum = totalAngularMomentum + particleData{counter, angularMomentumIdx};
end

disp('Plotting X Angular Momentum');

fig = figure('Visible', 'off');
    title('Angular Momentum - X Direction');
    xlabel('Time [s]');
    ylabel('X Angular Momentum [kg*m/s]');
    
    hold on
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, angularMomentumIdx}(:,1), ...
            'DisplayName', ['Particle ', int2str(counter)], ...
            'Color', cmap(counter, :));
    end
    plot(timeVector, totalAngularMomentum(:,1), 'Color', 'black', ...
        'LineStyle', '-', ...
        'LineWidth', 1.0, ...
        'DisplayName', 'Total X Angular Momentum');
    legend('show');
    
    disp('Saving');
    
    saveas(fig, [outputMATLAB, 'X_angular_momentum_plot.png']);    
    hold off  

disp('Plotting Y Angular Momentum');

fig = figure('Visible', 'off');
    title('Angular Momentum - Y Direction');
    xlabel('Time [s]');
    ylabel('Y Angular Momentum [kg*m/s]');
    
    hold on
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, angularMomentumIdx}(:,2), ...
            'DisplayName', ['Particle ', int2str(counter)], ...
            'Color', cmap(counter, :));
    end
    plot(timeVector, totalAngularMomentum(:,2), 'Color', 'black', ...
        'LineStyle', '-', ...
        'LineWidth', 1.0, ...
        'DisplayName', 'Total Y Angular Momentum');
    legend('show');
    
    disp('Saving');
    
    saveas(fig, [outputMATLAB, 'Y_angular_momentum_plot.png']);     
    hold off  

disp('Plotting Z Angular Momentum');

fig = figure('Visible', 'off');
    title('Angular Momentum - Z Direction');
    xlabel('Time [s]');
    ylabel('Z Angular Momentum [kg*m/s]');
    
    hold on
    
    for counter = 1 : nParticles
        plot(timeVector, particleData{counter, angularMomentumIdx}(:,3), ...
            'DisplayName', ['Particle ', int2str(counter)], ...
            'Color', cmap(counter, :));
    end
    plot(timeVector, totalAngularMomentum(:,3), 'Color', 'black', ...
        'LineStyle', '-', ...
        'LineWidth', 1.0, ...
        'DisplayName', 'Total Z Angular Momentum');
    legend('show');
    
    disp('Saving');
    
    saveas(fig, [outputMATLAB, 'Z_angular_momentum_plot.png']);    
    hold off  

disp('Done');

%% ===== Generate Movie =====
disp('Generating Movie');

timeSkip = 100;
disp(['Skipping ', int2str(timeSkip), ' time steps per frame']);

video = VideoWriter([outputMATLAB, 'outputVideo.avi']);

figure('Visible', 'off');
open(video)

xPos = zeros(nParticles, nTimeSteps);
yPos = zeros(nParticles, nTimeSteps);

xMin = zeros(nParticles, 1);
yMin = zeros(nParticles, 1);
xMax = zeros(nParticles, 1);
yMax = zeros(nParticles, 1);

for i = 1 : nParticles
    for j = 1 : nTimeSteps
        xPos(i, j) = particleData{i,positionIdx}(j,1);
        yPos(i, j) = particleData{i,positionIdx}(j,2);
    end
    xMin(i) = min(xPos(i,:));
    xMax(i) = max(xPos(i,:));
    yMin(i) = min(yPos(i,:));
    yMax(i) = max(yPos(i,:));
end

axis([min(xMin) - max(radius), max(xMax) + max(radius), min(yMin) - max(radius), max(yMax) + max(radius)]);
axis equal

Frame(nTimeSteps) = struct('cdata',[],'colormap',[]);
for j = 1 : timeSkip : nTimeSteps
    title([num2str(initialTime + (j-1)*timeStep), 's']);
    
    % Get center coordinates
    X = xPos(:, j);
    Y = yPos(:, j);
    centers = [X, Y];
    
    % Clear circles drawn before
    cla
    
    axis([min(xMin) - max(radius), max(xMax) + max(radius), min(yMin) - max(radius), max(yMax) + max(radius)]);
    axis equal
    set(gca,'Color',[0.8 0.8 0.8]);
    
    % Plot circles
    for counter = 1 : nParticles
        viscircles(centers(counter, :), radius(counter), 'EdgeColor', cmap(counter, :));
    end
    
    % Write to video
    Frame(j) = getframe(gcf);
    writeVideo(video, Frame(j));
end
close(video);

disp('Done');


% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Finished');