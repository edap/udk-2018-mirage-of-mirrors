## Drawing symmetries

This sketch draws on the right side of the screen what was drawn in the left side.


## openFrameworks 

## Exercise

Make your own symmetryc drawing app, the wilder&weirder, the better. 

- Have a look at the `drawCircle` method. Implement your own draw method drawing something that is not a circle. You can find inspiration in these chapters of the ofBook, [1](http://openframeworks.cc/ofBook/chapters/intro_to_graphics.html#brusheswithbasicshapes) & [2](http://openframeworks.cc/ofBook/chapters/lines.html#drawaline), in the `examples/graphics` folder, 
- These lines flip the FBO horizontally:

```cpp
ofTexture flipped = fbo.getTexture();
float pos = ofGetWidth() / 2.;
flipped.draw(ofGetWidth(), 0, -pos, ofGetHeight());
```

Can you imagine other ways to divide the screen maintaining a kind of simmetry?

- The app draws circles dragging the mouse. Which other types of interaction can you imagine?



## References

[Rorschach test](https://en.wikipedia.org/wiki/Rorschach_test)

[Symmetry in Biology](https://en.wikipedia.org/wiki/Symmetry_in_biology)
