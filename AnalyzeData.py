#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Aug 13 13:14:07 2022

@author: Harsh Godbole

This script generates results in an HTML format using plotly libraries

"""
import numpy as np
import pandas as pd
import os
import plotly.graph_objects as go
import plotly.express as px

"""
Make global data plots from generated data
"""

def makeGlobalResults(filenames):
    
    data = pd.DataFrame()
    
    # Get all files other than the observer files
    for filename in filenames:
        if '.txt' in filename and 'Observer' not in filename:
            data[filename[:-4]] = pd.read_csv("Generated/" + filename, header=None)


    # Convert Simulation time to hrs: 
    
    data['mSimulationTime'] = data['mSimulationTime'] / 3600.0;

    # Create figure and add one scatter trace
    fig = go.Figure()

    fig.add_trace(go.Scatter(
        x=data['mSimulationTime'], 
        y=data['mSimulationTime'],
        visible=True,
        mode='markers',
        )
              )

    # Create x and y buttons
    y_buttons = []

    for column in data.columns:
    
        y_buttons.append(dict(method='restyle',
                              label=column,
                              args=[{'y': [data[column]]}]
                              )
                         )

    # Pass buttons to the updatemenus argument
    fig.update_layout(updatemenus=[dict(buttons=y_buttons, showactive = True, direction='down', x=-0.01, y=1.0)], 
                      xaxis_title  = 'Simulation time (hrs)',
                      yaxis_title  = 'Collect Variable',
                      title='Evtol Simulation: Total collected data, for variable units refer respective .h files')

    fig.write_html('results//Simulation Collect.html', auto_open=True)

    return data, fig

"""
Make the observer data plots from generated data
"""
def plotObserverData(filename, plotTitle, xName, yName, legendName):
    
    
    data = pd.DataFrame()
    
    # Define col names for observer collect
    col_names = ['ALPHA', 'BETA', 'CHARLIE', 'DELTA', 'ECHO']
     
    data = pd.read_csv("Generated/" + filename, sep=',', header=None, names=col_names )
            
    data['mSimulationTime'] = pd.read_csv("Generated/mSimulationTime.txt", header=None)
            
    # Convert Simulation time to hrs: 
    
    data['mSimulationTime'] = data['mSimulationTime'] / 3600.0;
    data.apply(pd.to_numeric)
    
    # Make plotly figure
    fig = px.line(data, x='mSimulationTime', y=col_names)
    
    titleInfo = plotTitle + ":    " ;
    
    for colname in col_names:
        titleInfo = titleInfo + colname + ' : ' + f'{data[colname].iloc[-1]:.4f}' + ',   '
    
    # Update layout
    fig.update_layout(
    title        = titleInfo,
    xaxis_title  = xName,
    yaxis_title  = yName,
    legend_title = legendName)
    
    # Write to html file    
    fig.write_html("results//" + plotTitle + '.html', auto_open=True) 
    
    return data, fig

"""
Main Script
"""

filenames = os.listdir('Generated/')
filenames.sort()

makeGlobalResults(filenames)

data,fig = plotObserverData('22_Observer_sAvgTimeInCharging.txt',  'Average time charging (hrs)', 'Simulation time (hrs)', 'Avg Time charging (hrs)',     'Aircraft Type')
data,fig = plotObserverData('22_Observer_sAvgTimeInFlight.txt',    'Average time in flight (hrs)','Simulation time (hrs)', 'Avg Time in Flight (hrs)',    'Aircraft Type')
data,fig = plotObserverData('22_Observer_sAvgTimeInQueue.txt',     'Average time queue (hrs)',    'Simulation time (hrs)', 'Avg Time in Queue (hrs)',     'Aircraft Type')
data,fig = plotObserverData('22_Observer_sTotalPassengerMiles.txt','Total passenger-miles',       'Simulation time (hrs)', 'Total passenger-miles (hrs)', 'Aircraft Type')
data,fig = plotObserverData('22_Observer_sMaxNumOfFaults.txt',     'Max number of faults',        'Simulation time (hrs)', 'Avg time charging (hrs)',     'Aircraft Type')
data,fig = plotObserverData('22_Observer_sVehicleCount.txt',       'Number of vehicles spawned',  'Simulation time (hrs)', 'Number of vehicles spawned',  'Aircraft Type')








