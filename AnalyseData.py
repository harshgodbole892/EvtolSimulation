#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Aug 13 13:14:07 2022

@author: McGillDocs
"""
import numpy as np
import pandas as pd
import os
import plotly.graph_objects as go
import plotly.express as px


def makeGlobalResults(filenames):
    
    data = pd.DataFrame()
    
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
    fig.update_layout(updatemenus=[dict(buttons=y_buttons, showactive = True, direction='down', x=-0.01, y=0.5)], title='Evtol Simulation Collected Data')

    fig.write_html('results.html', auto_open=True)

    return data, fig

"""
Make the observer dataframe from generated data
"""
def makeObserverData(filename):
    
    
    data = pd.DataFrame()
    
    col_names = ['ALPHA', 'BETA', 'CHARLIE', 'DELTA', 'ECHO']
    
    data = pd.read_csv("Generated/" + filename, sep=',', header=None, names=col_names )
            
    data['mSimulationTime'] = pd.read_csv("Generated/mSimulationTime.txt", header=None)
            
    # Convert Simulation time to hrs: 
    
    data['mSimulationTime'] = data['mSimulationTime'] / 3600.0;
    
    data.apply(pd.to_numeric)
    
    fig = px.line(data, x='mSimulationTime', y=col_names, title=filename)
                  #animation_frame="mSimulationTime", range_x=[0,3], range_y=[0,100])
    
    fig.write_html(filename + '.html', auto_open=True) 
    
    return data, fig

"""
Main Script
"""

filenames = os.listdir('Generated/')
filenames.sort()

makeGlobalResults(filenames)

data,fig = makeObserverData('22_Observer_sAvgTimeInCharging.txt')
data,fig = makeObserverData('22_Observer_sAvgTimeInFlight.txt')
data,fig = makeObserverData('22_Observer_sAvgTimeInQueue.txt')
data,fig = makeObserverData('22_Observer_sTotalPassengerMiles.txt')
data,fig = makeObserverData('22_Observer_sMaxNumOfFaults.txt')









