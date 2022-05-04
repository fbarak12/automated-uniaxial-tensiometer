data = readmatrix("C:\Users\fbara\OneDrive\Documents\latexrun10.csv");
[numRows,numCol]=size(data);
stress = zeros(numRows); %Create Stress array
strain = zeros(numRows); %Create Strain array

%Get dimensions of sample
specimenWidth = input("Enter Width of Specimen (mm):");
specimenLength = input("Enter Length of Specimen (mm):");
specimenDepth = input("Enter Depth/Thickness of Specimen (mm):");

crossArea = specimenWidth*specimenDepth;

for i = 1:numRows
    stress(i) = (data(i,2)/crossArea);
    strain(i) = (data(i,1)+specimenLength/specimenLength);
end

%Find UTS; note force unit is grams, crossArea is mm^2
maxForce = max(data(:,2));
UTS = (maxForce*0.00981)/(crossArea/1000000); % N/m^2

utsMPA = UTS/1000000; %Convert from Pa to MPa

%Find Young's Modulus
elasticStress = zeros(100);
elasticStrain = zeros(100);

%test
%disp(data(1,1)) col 1 is elongation
%disp(data(5,1))

for i = 1:100
    elasticStress(i) = data(i,2);
    elasticStrain(i) = data(i,1);
end

youngsMod = sum(elasticStress)/sum(elasticStrain);

%Print results
%X = sprintf('Ultimate Tensile Strength: %.2f MPa', utsMPA);
%disp(X)
fprintf('Ultimate Tensile Strength: %.2f MPa', utsMPA)
fprintf('\nYoungs Modulus: %.3f Pa', youngsMod)

plot(strain,stress)
title("Nitrile Sample Stress vs. Strain")
grid on
%text(0,-100,'this is test')
xlabel("Strain = \epsilon = (L-L_0)/L_0")
ylabel("Stress (N/m^2) = \sigma = F/A_0")