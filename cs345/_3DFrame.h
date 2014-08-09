/*
  @file _3DFrame.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3D Frame
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 12 Apr 2011
  @note This file includes many optimizations specifically for use with NXC on
    the Lego Mindstorm NXT 2.0.
*/

/*
  @fn     void _3D_Init( _F )
  @brief  Initializes a reference frame to the default 3D frame values.
  @pre    _F must be a float[12] or double[12].
  @param  _F -- The array to convert to a reference frame.
  @post   Sets F equal to the default reference frame.
  @note   This MUST be called on a reference frame in order for all other functions
            to work properly!
  @note   The preconditions for many functions require that a parameter "be a 
            refrence frame." That means this function MUST be called with that
            array before it becomes a reference frame!
  @note   The default reference frame is equivalent to the world reference frame.
  
  @fn     _3D_Copy( _A, _B )
  @brief  Copies the contents of frame A into frame B.
  @pre    None.
  @param  _A -- The reference frame to copy.
  @param  _B -- The reference frame to copy into.
  @post   Copies the contents of frame A into frame B.
  
  @fn     _3D_set_x( _F, _x ) 
  @brief  Sets the x coordinate of F to _x.
  @pre    _F is a reference frame.
  @param  _F -- The reference frame to set the x value of.
  @param  _x -- The x value to set F's x value to.
  @post   Sets the x coordinate of F to _x.
  
  @fn     _3D_set_y( _F, _y )
  @brief  Sets the y coordinate of F to _y.
  @pre    _F is a reference frame.
  @param  _F -- The reference frame to set the y value of.
  @param  _y -- The y value to set F's y value to.
  @post   Sets the y coordinate of F to _y.    
  
  @fn     _3D_set_z( _F, _z )
  @brief  Sets the z coordinate of F to _z.
  @pre    _F is a reference frame.
  @param  _F -- The reference frame to set the z value of.
  @param  _z -- The z value to set F's z value to.
  @post   Sets the z coordinate of F to _z. 
  
  @fn     void _3D_Print( float F[] )
  @brief  Prints the reference frame to the upper half of the Mindstorm LCD screen.
  @pre    F is a reference frame.
  @param  float F[] -- The reference frame to output.
  @post   Prints the reference frame to the upper half of the Mindstorm LCD screen.
  
  @fn     void _3D_Print_Upper( float F[] )
  @brief  Prints the reference frame to the upper half of the Mindstorm LCD screen.
  @pre    F is a reference frame.
  @param  float F[] -- The reference frame to output.
  @post   Prints the reference frame to the upper half of the Mindstorm LCD screen.
  
  @fn     void _3D_Print_Lower( float F[] )
  @brief  Prints the reference frame to the lower half of the Mindstorm LCD screen.
  @pre    F is a reference frame.
  @param  float F[] -- The reference frame to output.
  @post   Prints the reference frame to the lower half of the Mindstorm LCD screen.

  @fn     void _3D_Mult( float A[], float B[], float& C[] )
  @brief  Multiples frame A by frame B and stores the result in frame C.
  @pre    A, B, and C are reference frames.
  @param  float A[] -- The left hand side of the multiplication operation.
  @param  float B[] -- The right hand side of the multiplication operation.
  @param  float& C[] -- The frame to store the result of the multiplication in.
  @post   Multiplies frame A by frame B and stores the result in frame C.
  
  @fn     void _3D_set_rot_x( float& F[], float alpha )
  @brief  Sets F to the transformation frame for a rotation about the X axis by 
            alpha radians.
  @pre    F is a reference frame.
  @pre    alpha is a radian value.
  @param  float& F[] -- The reference frame to convert into a transformation frame.
  @param  float alpha -- The radian value to rotate about the X axis by.
  @post   Sets F to the transformation frame for a rotation about the X axis by
            alpha radians.
            
  @fn     void _3D_set_rot_y( float& F[], float beta )
  @brief  Sets F to the transformation frame for a rotation about the Y axis by 
            beta radians.
  @pre    F is a reference frame.
  @pre    beta is a radian value.
  @param  float& F[] -- The reference frame to convert into a transformation frame.
  @param  float beta -- The radian value to rotate about the Y axis by.
  @post   Sets F to the transformation frame for a rotation about the Y axis by
            beta radians.
            
  @fn     void _3D_set_rot_z( float& F[], float gamma )
  @brief  Sets F to the transformation frame for a rotation about the Z axis bz 
            gamma radians.
  @pre    F is a reference frame.
  @pre    gamma is a radian value.
  @param  float& F[] -- The reference frame to convert into a transformation frame.
  @param  float gamma -- The radian value to rotate about the Z axis bz.
  @post   Sets F to the transformation frame for a rotation about the Z axis bz
            gamma radians.

  @fn     void _3D_set_rot_euler_ZYZ( float& F[], float phi, float theta, float psi )
  @brief  Sets F to the transformation frame for a rotation about the Z, then Y,
            then Z axis, relative to the frame. This is an Euler rotation.
  @pre    F is a reference frame.
  @pre    phi, theta, and psi are radian values
  @param  float& F[] -- The reference fram eto convert into a transformation frame.
  @param  float phi -- The radian value to rotate about the Z axis the first time.
  @param  float theta -- The radian value to rotate about the Y axis.
  @param  float psi -- The radian value to rotate about the Z axis the second time.
  @post   Sets F to the transformation frame for a rotation about the Z, then Y,
            then Z axis, relative to the frame. This is an Euler rotation.
  
  @fn     void _3D_set_loc( float F[], float x, float y, float z, float& G[] )
  @brief  Sets the location of F to (x,y,z) and stores it in G.
  @pre    F and G are reference frames.
  @param  float F[] -- The reference frame to relocate.
  @param  float x -- The new x coordinate for F.
  @param  float y -- The new y coordinate for F.
  @param  float z -- The new z coordinate for F.
  @param  float& G[] -- The reference frame to store the relocated frame in.
  @post   Sets the location of F to (x,y,z) and stores it in G.
  
  @fn     void _3D_rot_x( float F[], float alpha, float& G[] )
  @brief  Rotates F about its X axis by a radian value alpha and stores the result
            in G.
  @pre    F and G are reference frames.
  @pre    alpha is a radian value.
  @param  float F[] -- The reference frame to rotate.
  @param  float alpha -- The radian value to rotate the frame by.
  @param  float& G[] -- The reference frame to store the result of the rotation in.
  @post   Rotates F about its X axis by a radian value alpha and stores the result
            in G.
            
  @fn     void _3D_rot_y( float F[], float beta, float& G[] )
  @brief  Rotates F about its Y axis by a radian value beta and stores the result
            in G.
  @pre    F and G are reference frames.
  @pre    beta is a radian value.
  @param  float F[] -- The reference frame to rotate.
  @param  float beta -- The radian value to rotate the frame by.
  @param  float& G[] -- The reference frame to store the result of the rotation in.
  @post   Rotates F about its Y axis by a radian value beta and stores the result
            in G.
            
  @fn     void _3D_rot_z( float F[], float gamma, float& G[] )
  @brief  Rotates F about its Z axis by a radian value gamma and stores the result
            in G.
  @pre    F and G are reference frames.
  @pre    gamma is a radian value.
  @param  float F[] -- The reference frame to rotate.
  @param  float gamma -- The radian value to rotate the frame by.
  @param  float& G[] -- The reference frame to store the result of the rotation in.
  @post   Rotates F about its Z axis by a radian value gamma and stores the result
            in G.
            
  @fn     void _3D_rot_euler_ZYZ( float F[], float phi, float theta, float psi, float& G[] )
  @brief  Rotates F about its Z then Y then Z axes by radian values phi, theta, and psi
            respectively and stores the result in G. 
  @pre    F and G are reference frames.
  @pre    phi, theta, and psi are radian values.
  @param  float F[] -- The reference frame to rotate.
  @param  float phi -- The radian value to rotate about the frame's Z axis by 
            the first time.
  @param  float theta -- The radian value to rotate about the frame's Y axis by.
  @param  float psi -- The radian value to rotate about the frame's Z axis by 
            the second time. 
  @post   Rotates F about its Z then Y then Z axes by radian values phi, theta, and psi
            respectively and stores the result in G. 
            
  @fn     void _3D_translate_rel( float F[], float x, float y, float z, float& G[] )
  @brief  Translates F by (x,y,z) relative to the orientation of its axes.
  @pre    F and G are reference frames.
  @param  float F[] -- The reference frame to translate.
  @param  float x -- The value to translate along F's x axis by.
  @param  float y -- The value to translate along F's y axis by.
  @param  float z -- The value to translate along F's z axis by.
  @param  float& G[] -- The reference frame to store the result of the translation in.
  
  @fn     void _3D_translate_abs( float F[], float x, float y, float z, float& G[] )
  @brief  Translates F by (x,y,z) relative to the orientation of the world reference frame.
  @pre    F and G are reference frames.
  @param  float F[] -- The reference frame to translate.
  @param  float x -- The value to translate along the world's x axis by.
  @param  float y -- The value to translate along the world's y axis by.
  @param  float z -- The value to translate along the world's z axis by.
  @param  float& G[] -- The reference frame to store the result of the translation in.

  @fn     void _3D_distance( float F[], float G[], float& d )
  @brief  Calculates the distance between F and G and stores it in d.
  @pre    F and G are reference frames.
  @param  float F[] -- The first reference frame.
  @param  float G[] -- The second reference frame.
  @param  float& d -- The number to store the distance between the two frames in.
  @post   Calculates the distance between F and G and stores it in d.
  
  @fn     void _3D_move( float F[], float G[] )
  @brief  Prints F to the upper half of the Mindstorm LCD screen and G to the lower.
  @pre    F and G are reference frames.
  @param  float F[] -- The reference frame to output to the upper half of the screen.
  @param  float G[] -- The reference frame to output to the lower half of the screen.
  @post   Prints F to the upper half of the Mindstorm LCD screen and G to the lower.
  
  @fn     void _3D_clear_rot( float& F[] )
  @brief  Sets the rotation matrix component of F to 0.
  @pre    F is a reference frame.
  @param  float& F[] -- The reference frame to clear the rotation matrix of.
  @post   Sets the rotation matrix component of F to 0.
  
  @fn     void _3D_reset_rot( float& F[] )
  @brief  Resets the rotation matrix of F to the world reference frame's rotation.
  @pre    F is a reference frame.
  @param  float& F[] -- The reference frame to reset the rotation matrix of.
  @post   Resets the rotation matrix of F to the world reference frame's rotation.
  
  @fn     void _3D_clear_loc( float& F[] )
  @brief  Sets the location of F to (0,0,0).
  @pre    F is a reference frame
  @param  float& F[] -- The reference frame to clear the location of.
  @post   Sets the location of F to (0,0,0).
*/

#ifndef _3DFRAMEH
#define _3DFRAMEH

#include "NXCDefs.h"

// The initial array structure for a 3D Frame.
float _3D_INIT_ARRAY[] = { 1.0, 0.0, 0.0, 0.0,
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0 };

#define _3D_Init( _F )      _F = _3D_INIT_ARRAY
#define _3D_Copy( _A, _B )  _B = _A

#define _3D_set_x( _F, _x ) _F[3] = _x
#define _3D_set_y( _F, _y ) _F[7] = _y
#define _3D_set_z( _F, _z ) _F[11] = _z

void     _3D_Print       ( float F[] );
void     _3D_Print_Upper ( float F[] );
void     _3D_Print_Lower ( float F[] );
                           
void     _3D_Mult        ( float A[], float B[], float& C[] );

void     _3D_set_rot_x   ( float& F[], float alpha );
void     _3D_set_rot_y   ( float& F[], float beta );
void     _3D_set_rot_z   ( float& F[], float gamma );
void     _3D_set_rot_euler_ZYZ( float& F[], float phi, float theta, float psi );

void     _3D_set_loc     ( float F[], float x, float y, float z, float& G[] );

void     _3D_rot_x       ( float F[], float alpha, float& G[] );
void     _3D_rot_y       ( float F[], float beta, float& G[] );
void     _3D_rot_z       ( float F[], float gamma, float& G[] );
void     _3D_rot_euler_ZYZ( float F[], float phi, float theta, float psi, float& G[] );
void     _3D_translate_rel( float F[], float x, float y, float z, float& G[] );
void     _3D_translate_abs( float F[], float x, float y, float z, float& G[] );

void     _3D_distance    ( float F[], float G[], float& d );
void     _3D_move        ( float F[], float G[] );

void     _3D_clear_rot   ( float& F[] );
void     _3D_reset_rot   ( float& F[] );
void     _3D_clear_loc   ( float& F[] );

/******************************************************************************/

void _3D_Print( float F[] )
{
  _3D_Print_Upper( F );
}

void _3D_Print_Upper( float F[] )
{
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 3; j++ )
       TextOut( i*24, LCD_LINE1-8*j, FormatNum( "%4.1f", F[(j*4) + i] ) );
}

void _3D_Print_Lower( float F[] )
{
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 3; j++ )
       TextOut( i*24, LCD_LINE5-8*j, FormatNum( "%4.1f", F[(j*4) + i] ) );
}

void _3D_Mult( float A[], float B[], float& C[] )
{
  // Access and store the elements of the source matrices to reduce accesses to
  // the array
  float A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11;
  float B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11;
  
  A0 = A[0]; A1 = A[1]; A2  = A[2];  A3  = A[3];
  A4 = A[4]; A5 = A[5]; A6  = A[6];  A7  = A[7];
  A8 = A[8]; A9 = A[9]; A10 = A[10]; A11 = A[11];
  
  B0 = B[0]; B1 = B[1]; B2  = B[2];  B3  = B[3];
  B4 = B[4]; B5 = B[5]; B6  = B[6];  B7  = B[7];
  B8 = B[8]; B9 = B[9]; B10 = B[10]; B11 = B[11];
  
  // Perform and store the results of the multiplication
  C[0]  = A0*B0 + A1*B4 + A2*B8;
  C[1]  = A0*B1 + A1*B5 + A2*B9;
  C[2]  = A0*B2 + A1*B6 + A2*B10;
  C[3]  = A0*B3 + A1*B7 + A2*B11 + A3;
  C[4]  = A4*B0 + A5*B4 + A6*B8;
  C[5]  = A4*B1 + A5*B5 + A6*B9;
  C[6]  = A4*B2 + A5*B6 + A6*B10;
  C[7]  = A4*B3 + A5*B7 + A6*B11 + A7;
  C[8]  = A8*B0 + A9*B4 + A10*B8;
  C[9]  = A8*B1 + A9*B5 + A10*B9;
  C[10] = A8*B2 + A9*B6 + A10*B10;
  C[11] = A8*B3 + A9*B7 + A10*B11 + A11;  
}

void _3D_set_rot_x( float& F[], float alpha )
{
  float sa  = sin(alpha);
  float ca  = cos(alpha);
  float nsa = -sa;
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  // Create the transformation matrix
  ArrayBuild( F, 1.0, 0.0, 0.0, F3,
                 0.0, ca,  nsa, F7,
                 0.0, sa,  ca,  F11 );  
}

void _3D_set_rot_y( float& F[], float beta )
{
  float sb  = sin( beta );
  float cb  = cos( beta );
  float nsb = -sb;
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  // Create the transformation matrix
  ArrayBuild( F, cb,  0.0, sb,  F3,
                 0.0, 1.0, 0.0, F7,
                 nsb, 0.0, cb,  F11 );
}

void _3D_set_rot_z( float& F[], float gamma )
{
  float sg  = sin( gamma );
  float cg  = cos( gamma );
  float nsg = -sg;
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  // Create the transformation matrix
  ArrayBuild( F, cg,  nsg, 0.0, F3,
                 sg,  cg,  0.0, F7,
                 0.0, 0.0, 1.0, F11 );
}

void _3D_set_rot_euler_ZYZ( float& F[], float phi, float theta, float psi )
{
  float F0, F1, F2, F4, F5, F6, F8, F9, F10;

  float sphi   = sin( phi );
  float cphi   = cos( phi );
  float stheta = sin( theta );
  float ctheta = cos( theta );
  float spsi   = sin( psi );
  float cpsi   = cos( psi );
  
  F0 = (cphi * ctheta * cpsi) - (sphi * spsi);
  F1 = -(cphi * ctheta * cpsi) - (sphi * cpsi);
  F2 = cphi * stheta;

  F4 = (sphi * ctheta * cpsi) + (cphi * spsi);
  F5 = -(sphi * ctheta * spsi) + (cphi * cpsi);
  F6 = sphi * stheta;
  
  F8 = -stheta * cpsi;
  F9 = stheta * spsi;
  F10 = ctheta;
  
  // Create the transformation matrix
  ArrayBuild( F, F0, F1, F2,  0.0,
                 F4, F5, F6,  0.0,
                 F8, F9, F10, 0.0 );  
}

void _3D_rot_x( float F[], float alpha, float& G[] )
{
  float rot_x[12];
  float temp[12];
  
  _3D_set_rot_x( rot_x, alpha );

  _3D_Mult( F, rot_x, G );
}

void _3D_rot_y( float F[], float beta, float& G[] )
{
  float rot_y[12];
  float temp[12];
  
  _3D_set_rot_y( rot_y, beta );

  _3D_Mult( F, rot_y, G );
}

void _3D_rot_z( float F[], float gamma, float& G[] )
{
  float rot_z[12];
  float temp[12];
  
  _3D_set_rot_z( rot_z, gamma );

  _3D_Mult( F, rot_z, G );
}

void _3D_rot_euler_ZYZ( float F[], float phi, float theta, float psi, float& G[] )
{
  float rot_euler[12];
  float temp[12];
  
  _3D_set_rot_euler_ZYZ( rot_euler, phi, theta, psi );
  
  _3D_Mult( F, rot_euler, G );
}

void _3D_set_loc( float F[], float x, float y, float z, float& G[] )
{
  _3D_set_x( F, x );
  _3D_set_y( F, y );
  _3D_set_z( F, z );
}

void _3D_translate_rel( float F[], float x, float y, float z, float& G[] )
{
  G = F;
  
  G[3]  = F[0]*x + F[1]*y + F[2]*z  + F[3];
  G[7]  = F[4]*x + F[5]*y + F[6]*z  + F[7];
  G[11] = F[8]*x + F[9]*y + F[10]*z + F[11];
}

void _3D_translate_abs( float F[], float x, float y, float z, float& G[] )
{
  G = F;

  G[3]  = F[3]  + x;
  G[7]  = F[7]  + y;
  G[11] = F[11] + z;
}

void _3D_distance( float F[], float G[], float& d )
{
  // Store the differences in the coordinates between F and G
  float dx = F[3]  - G[3];
  float dy = F[7]  - G[7];
  float dz = F[11] - G[11];
  
  // Calculate and store the distance between F and G
  d = sqrt( (dx*dx) + (dy*dy) + (dz*dz) );
}

void _3D_move( float F[], float G[] )
{
  _3D_Print_Upper( F );
  _3D_Print_Lower( G );
}

void _3D_clear_rot( float& F[] )
{
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  // Create the transformation matrix
  ArrayBuild( F, 0.0, 0.0, 0.0, F3,
                 0.0, 0.0, 0.0, F7,
                 0.0, 0.0, 0.0, F11 );  
}

void _3D_reset_rot( float& F[] )
{
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  // Create the transformation matrix
  ArrayBuild( F, 1.0, 0.0, 0.0, F3,
                 0.0, 1.0, 0.0, F7,
                 0.0, 0.0, 1.0, F11 );  
}

void _3D_clear_loc( float& F[] )
{
  F[3]  = 0.0;
  F[7]  = 0.0;
  F[11] = 0.0;
}

#endif
