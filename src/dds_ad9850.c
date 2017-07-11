/*
 * AD9850 DDS Header for Arduino VFO Project
 *
 * Eng. Felipe Navarro
 * 11/07/2017
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 #include <dds_ad9850.h>

 
 void setup_ad9850 (void)
 {
     DDS.begin(W_CLK_PIN, FQ_UD_PIN, DATA_PIN, RESET_PIN);
     DDS.calibrate(XTAL_Freq);
 }

void VFO_setfreq_up (void)
 {  
    freq += step_size[step_index];
    DDS.setfreq(freq , phase);
 }

 void VFO_setfreq_down (void)
 {
    freq -= step_size[step_index];
    DDS.setfreq(freq , phase);  
 }


 void VFO_Step_Up (void)
 {  
    step_index++;
    //If Step_Index greater than max, return to zero step
    ( step_index > step_max ) ? 0 : step_index ;
 }

 void VFO_Step_Down (void)
 {
    step_index--;
    ( step_index < 0 ) ? step_max : step_index ;
 }

 void band_up (void)
 {
    band_index++;
    //Band index greater than max, go to zero
    ( band_index > band_max ) ? 0;
    freq = 0;
    freq = IF_Freq + band[band_index];
 }

 void band_down (void)
 {
    band_index--;
    //Band Index Less Than Zero ? Go to last band
    ( band_index < 0 ) ? band_max;
    freq = 0;
    freq = IF_Freq + band[band_index];    
 }
