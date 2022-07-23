# INSA Projects

This folder contains an insight about different school projects realized at INSA (reports, presentations, screenshots ... etc). Source codes are subjects to INSA copyright rules, therefore they couldn't be uploaded.  

## Automata Creator

A project to practice software engineering and modeling, achevied in a team of 6 developers.  
AuotmataCreator was designed to assist professors and researchers in drawing Automatas and State Machines, especially researchers working on language theory and operational research algorithms.  
The softwaren, developed in Python3, comes with a user-friendly GUI developed using PyQt5. It supports automation algorithms to assist the user with his task (pre-configured Automata models, re-arranging elements ... etc). Drawn Automatas can be saved into .automata files if the user wishes to pick up his work later on, or exported in PDF files or image formats (PNG, JPEG, SVG) using LaTeX/TikZ library.  

## NeTree

A network and system programming project in C, done in a team of 4 students.  
The project's core purpose is to implement a tree-based networking application. So the main features concerned, among others, message broadcast in a tree, unicast message exchange and network resilinece and recovery in case of a node's death. It also supports a security feature to encrypt exchanged packets. The advantage of this tree-based network architecture is its scalability and charge distribution capacity.  
The application layer implements a system administration feature. Actually, using the application a network/system administrator can execute any Bash command, on all or a selected number of nodes in the network (depending on his/her need).  

## Smart Drone

The project, done in a team of 2 students, is basically a Machine Learning algorithms for Quad-copters.  
The drone will completely lose its aero-dynamic balance, in case on of its 4 rotors breaks down. Using a re(inforcement learning algorithm, the drone can actually learn how to maintain its balance up in the air at least, and eventually fly by commanding the 4 aero-dynamic variables (Pitch, Roll, Yaw & Acceleration).  
A simulator we implemented was capable of generating graphs in order to observe the algorithm's behavior. It uses the matplotlib library for Python3.  

## OpenNebula infrastructure

The project, of 3 students, aims mainly at deploying a Cloud-based infrastructure using OpenNebula, dynamically sizeable depending on the charge uphold. One server and 2 workers were deployed for tests. An auto-scaling feature using OneFlow was integrated into the solution.  
For example, if we assume that one VM on a worker is running some website's backend, and this backend suddenly over-flooded with requests, then the worker will automatically deploy a second VM (or even third, fourth ... accordingly) to handle the traffic. These clone VMs can be deployed on any worker, as long as it's configured on the server. They will be deleted, if the traffic pick drops.
