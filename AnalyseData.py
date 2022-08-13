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


data = pd.DataFrame()
filenames = os.listdir('Generated/')
filenames.sort()

for filename in filenames:
    if '.txt' in filename:
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
x_buttons = []
y_buttons = []

for column in data.columns:
    x_buttons.append(dict(method='restyle',
                        label=column,
                        args=[{'x': [data[column]]}]
                        )
                )
    
    y_buttons.append(dict(method='restyle',
                        label=column,
                        args=[{'y': [data[column]]}]
                        )
                )

# Pass buttons to the updatemenus argument
fig.update_layout(updatemenus=[dict(buttons=x_buttons, showactive = True, direction='up', x=0.5, y=-0.1),
                               dict(buttons=y_buttons, showactive = True, direction='down', x=-0.01, y=0.5)])

fig.write_html('results.html', auto_open=True)