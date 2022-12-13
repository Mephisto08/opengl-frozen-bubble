#version 300 es

in mediump vec2    pos;                        
uniform mediump float   phase;

out mediump vec4 color;
                                                       
   void  main()                                        
   {                                                   
      color  =  vec4( 1., 0.9, 0.7, 1.0 ); //*     
        //cos( 30.*sqrt(pos.x*pos.x + 1.5*pos.y*pos.y)   
        //     + atan(pos.y,pos.x) - phase );            
   }   