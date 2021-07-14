/*
The MIT License (MIT)

Copyright (c) 2015 Lachlan Tychsen-Smith (lachlan.ts@gmail.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// BUILD ONLY WITH O0 or O1

extern "C" {
	float sqrtf(float f)
	{
		__asm (
			//fast invsqrt approx
			"vmov.f32 		d1, d0					\n\t"	//d1 = d0
			"vrsqrte.f32 	d0, d0					\n\t"	//d0 = ~ 1.0 / sqrt(d0)
			"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1
			"vrsqrts.f32 	d3, d2, d0				\n\t"	//d3 = (3 - d0 * d2) / 2 	
			"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3
			"vmul.f32 		d2, d0, d1				\n\t"	//d2 = d0 * d1	
			"vrsqrts.f32 	d3, d2, d0				\n\t"	//d4 = (3 - d0 * d3) / 2	
			"vmul.f32 		d0, d0, d3				\n\t"	//d0 = d0 * d3	

			//fast reciporical approximation
			"vrecpe.f32		d1, d0					\n\t"	//d1 = ~ 1 / d0; 
			"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
			"vmul.f32		d1, d1, d2				\n\t"	//d1 = d1 * d2; 
			"vrecps.f32		d2, d1, d0				\n\t"	//d2 = 2.0 - d1 * d0; 
			"vmul.f32		d0, d1, d2				\n\t"	//d0 = d1 * d2; 
			);
	}

	float ldexpf(float m, int e)
	{
		float r;
		__asm (
			"lsl 			r0, r0, #23				\n\t"	//r0 = r0 << 23	
			"vdup.i32 		d1, r0					\n\t"	//d1 = {r0, r0}
			"vadd.i32 		d0, d0, d1				\n\t"	//d0 = d0 + d1
			);
	}
}