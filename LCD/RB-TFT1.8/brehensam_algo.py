   
# Python 3 program for Bresenham’s Line Generation 
# Assumptions : 
# 1) Line is drawn from left to right. 
# 2) x1 < x2 and y1 < y2 
# 3) Slope of the line is between 0 and 1. 
# We draw a line from lower left to upper 
# right. 

import numpy as np
from matplotlib import pyplot as plt  

# function for line generation 
def bresenham(x0, y0, x1, y1): 

    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    sx = -1 if x0 > x1 else 1
    sy = -1 if y0 > y1 else 1
    err = dx - dy
    points = [(x0, y0)]
    while x0 != x1 or y0 != y1:
        e2 = err * 2
        if e2 > -dy:
            err -= dy
            x0 += sx
        if e2 < dx:
            err += dx
            y0 += sy
        points.append((x0, y0))

    return points


def calculate_bresenham(start_point: tuple[int, int], end_point: tuple[int, int]):
    x0, y0 = start_point
    x1, y1 = end_point
    bresenham_list = bresenham(x0, y0, x1, y1)
    return np.array(bresenham_list)



xx1 = calculate_bresenham((30,50),(100, 40))
xx2 = calculate_bresenham((30, 50), (20, 60))

x1, y1 = zip(*xx1)
x2, y2 = zip(*xx2)

plt.figure()
plt.plot(x1,y1,'+g')
plt.plot(x2,y2,'*b')
plt.show()

'''
    d_x = (x2 - x1) 
    d_y = (y2 - y1)

    if(d_x > d_y):
        max_delta = d_x
    else:
        max_delta = d_y
    
    y_v = np.zeros(max_delta)
    x_v = np.zeros(max_delta)
    
    print(f"D_x = {(x2 - x1)} et D_y = {(y2 - y1)} / MM = {(y2 - y1) / (x2 - x1)} \n") 
    
    if(d_x > d_y):
        m_new = 2 * (y2 - y1) 
        slope_error_new = m_new - (x2 - x1) 
        y = y1 
        cpt = 0
        for x in range(x1, x2+1): 
            x_v[cpt] = x
            print(f"({x} , {y}) - {slope_error_new}") 
      
            # Add slope to increment angle formed 
            slope_error_new = slope_error_new + m_new 
      
            # Slope error reached limit, time to 
            # increment y and update slope error. 
            if (slope_error_new >= 0): 
                y = y+1
                slope_error_new = slope_error_new - 2 * (x2 - x1)         
            y_v[cpt] = y
    else:
        m_new = 2 * (y2 - y1) 
        slope_error_new = m_new - (x2 - x1) 
        x = x1 
        cpt = 0
        for y in range(y1, y2+1): 
            y_v[cpt] = y
            print(f"({x} , {y}) - {slope_error_new}") 
      
            # Add slope to increment angle formed 
            slope_error_new = slope_error_new + m_new 
      
            # Slope error reached limit, time to 
            # increment y and update slope error. 
            if (slope_error_new >= 0): 
                x = x+1
                slope_error_new = slope_error_new - 2 * (x2 - x1)         
            x_v[cpt] = x

  
    return x_v, y_v
  
# Driver code 
if __name__ == '__main__': 
    x1, y1 = 2, 3
    x2, y2 = 5, 15
  
    # Function call 
    x, y = bresenham(x1, y1, x2, y2) 
    
    plt.figure()
    plt.plot(x, y)
    plt.show()
  
# This code is contributed by ash264 
'''