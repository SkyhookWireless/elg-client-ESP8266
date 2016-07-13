<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="1" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="7" fill="1" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="yes" active="yes"/>
<layer number="101" name="Patch_Top" color="7" fill="1" visible="yes" active="yes"/>
<layer number="102" name="Mittellin" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="Stiffner" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="7" fill="1" visible="yes" active="yes"/>
<layer number="105" name="Beschreib" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="BGA-Top" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="BD-Top" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="tBridges" color="7" fill="1" visible="yes" active="yes"/>
<layer number="109" name="tBPL" color="7" fill="1" visible="yes" active="yes"/>
<layer number="110" name="bBPL" color="7" fill="1" visible="yes" active="yes"/>
<layer number="111" name="MPL" color="7" fill="1" visible="yes" active="yes"/>
<layer number="112" name="tSilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="113" name="ReferenceLS" color="7" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="7" fill="1" visible="yes" active="yes"/>
<layer number="118" name="Rect_Pads" color="7" fill="1" visible="yes" active="yes"/>
<layer number="121" name="sName" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bPlace" color="7" fill="1" visible="yes" active="yes"/>
<layer number="123" name="tTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="124" name="bTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="126" name="_bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="127" name="_tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="128" name="_bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="129" name="Mask" color="7" fill="1" visible="yes" active="yes"/>
<layer number="131" name="tAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="132" name="bAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="150" name="Notes" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="152" name="_bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="153" name="FabDoc1" color="7" fill="1" visible="yes" active="yes"/>
<layer number="154" name="FabDoc2" color="7" fill="1" visible="yes" active="yes"/>
<layer number="155" name="FabDoc3" color="7" fill="1" visible="yes" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="218" name="218bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="219" name="219bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="220" name="220bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="221" name="221bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="222" name="222bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="223" name="223bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="224" name="224bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="225" name="225bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="226" name="226bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="227" name="227bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="228" name="228bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="229" name="229bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="230" name="230bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="231" name="Eagle3D_PG1" color="7" fill="1" visible="yes" active="yes"/>
<layer number="232" name="Eagle3D_PG2" color="7" fill="1" visible="yes" active="yes"/>
<layer number="233" name="Eagle3D_PG3" color="7" fill="1" visible="yes" active="yes"/>
<layer number="248" name="Housing" color="7" fill="1" visible="yes" active="yes"/>
<layer number="249" name="Edge" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="7" fill="1" visible="yes" active="yes"/>
<layer number="251" name="SMDround" color="7" fill="1" visible="yes" active="yes"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
<layer number="255" name="routoute" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Adafruit ESP8266 Feather">
<description>Generated from &lt;b&gt;Adafruit ESP8266 Feather.sch&lt;/b&gt;&lt;p&gt;
by exp-lbrs.ulp</description>
<packages>
</packages>
<symbols>
<symbol name="MICROBUILDER_FRAME_A4">
<wire x1="256.54" y1="3.81" x2="256.54" y2="36.83" width="0.1016" layer="94"/>
<frame x1="0" y1="0" x2="260.35" y2="179.07" columns="6" rows="4" layer="94"/>
</symbol>
<symbol name="MICROBUILDER_FRAME_DOCFIELD">
<description>&lt;p&gt;Frame doc - Courtesy Robert Starr (bobstarr.net)&lt;/p&gt;</description>
<circle x="109.2327" y="31.4198" radius="1.4199" width="0.254" layer="94"/>
<wire x1="20.0152" y1="1.5748" x2="95.5802" y2="1.5748" width="0.6096" layer="94"/>
<wire x1="20.0152" y1="1.5748" x2="20.0152" y2="6.6548" width="0.3048" layer="94"/>
<wire x1="20.0152" y1="6.6548" x2="88.5952" y2="6.6548" width="0.3048" layer="94"/>
<wire x1="20.0152" y1="6.6548" x2="20.0152" y2="10.4648" width="0.3048" layer="94"/>
<wire x1="20.0152" y1="10.4648" x2="20.0152" y2="16.8148" width="0.3048" layer="94"/>
<wire x1="121.6152" y1="16.8148" x2="121.6152" y2="6.6548" width="0.6096" layer="94"/>
<wire x1="95.5802" y1="6.6548" x2="95.5802" y2="1.5748" width="0.3048" layer="94"/>
<wire x1="95.5802" y1="1.5748" x2="121.6152" y2="1.5748" width="0.6096" layer="94"/>
<wire x1="88.5952" y1="16.8148" x2="88.5952" y2="6.6548" width="0.3048" layer="94"/>
<wire x1="88.5952" y1="6.6548" x2="95.5802" y2="6.6548" width="0.3048" layer="94"/>
<wire x1="121.6152" y1="16.8148" x2="110.1852" y2="16.8148" width="0.3048" layer="94"/>
<wire x1="110.1852" y1="16.8148" x2="88.5952" y2="16.8148" width="0.3048" layer="94"/>
<wire x1="88.5952" y1="16.8148" x2="20.0152" y2="16.8148" width="0.3048" layer="94"/>
<wire x1="95.5802" y1="6.6548" x2="121.6152" y2="6.6548" width="0.3048" layer="94"/>
<wire x1="121.6152" y1="6.6548" x2="121.6152" y2="1.5748" width="0.6096" layer="94"/>
<wire x1="20.0152" y1="16.8148" x2="20.0152" y2="19.3548" width="0.3048" layer="94"/>
<wire x1="20.0152" y1="19.3548" x2="20.0152" y2="28.2448" width="0.3048" layer="94"/>
<wire x1="121.6152" y1="34.5948" x2="105.7402" y2="34.5948" width="0.6096" layer="94"/>
<wire x1="105.7402" y1="34.5948" x2="20.0152" y2="34.5948" width="0.6096" layer="94"/>
<wire x1="121.6152" y1="34.5948" x2="121.6152" y2="28.2448" width="0.6096" layer="94"/>
<wire x1="20.0152" y1="28.2448" x2="105.7402" y2="28.2448" width="0.3048" layer="94"/>
<wire x1="105.7402" y1="28.2448" x2="110.1852" y2="28.2448" width="0.3048" layer="94"/>
<wire x1="110.1852" y1="28.2448" x2="121.6152" y2="28.2448" width="0.3048" layer="94"/>
<wire x1="20.0152" y1="28.2448" x2="20.0152" y2="34.5948" width="0.3048" layer="94"/>
<wire x1="121.6152" y1="28.2448" x2="121.6152" y2="16.8148" width="0.6096" layer="94"/>
<wire x1="101.2952" y1="13.3223" x2="102.2477" y2="13.3223" width="0.254" layer="94"/>
<wire x1="110.1852" y1="28.2448" x2="110.1852" y2="16.8148" width="0.3048" layer="94"/>
<wire x1="105.7402" y1="28.2448" x2="105.7402" y2="34.5948" width="0.3048" layer="94"/>
<wire x1="20.0152" y1="34.5948" x2="-0.3048" y2="34.5948" width="0.6096" layer="94"/>
<wire x1="-0.3048" y1="34.5948" x2="-0.3048" y2="28.2448" width="0.6096" layer="94"/>
<wire x1="-0.3048" y1="28.2448" x2="-0.3048" y2="19.3548" width="0.6096" layer="94"/>
<wire x1="-0.3048" y1="19.3548" x2="-0.3048" y2="10.4648" width="0.6096" layer="94"/>
<wire x1="-0.3048" y1="10.4648" x2="-0.3048" y2="1.5748" width="0.6096" layer="94"/>
<wire x1="-0.3048" y1="1.5748" x2="20.0152" y2="1.5748" width="0.6096" layer="94"/>
<wire x1="-0.3048" y1="28.2448" x2="20.0152" y2="28.2448" width="0.3048" layer="94"/>
<wire x1="-0.3048" y1="19.3548" x2="20.0152" y2="19.3548" width="0.3048" layer="94"/>
<wire x1="-0.3048" y1="10.4648" x2="20.0152" y2="10.4648" width="0.3048" layer="94"/>
<text x="108.9152" y="2.8448" size="2.54" layer="94" font="vector" ratio="10">&gt;SHEET</text>
<text x="112.4077" y="24.4348" size="2.54" layer="94" font="vector" ratio="12">REV</text>
<text x="21.2852" y="24.4348" size="2.54" layer="94" font="vector" ratio="12">TITLE</text>
<text x="89.8652" y="13.0048" size="2.54" layer="94" font="vector" ratio="12">DRG</text>
<text x="100.9777" y="13.9573" size="2.1844" layer="94" ratio="12">o</text>
<text x="33.0327" y="2.8448" size="2.54" layer="94" ratio="10">&gt;DRAWING_NAME</text>
<text x="98.4377" y="13.0048" size="2.54" layer="94" font="vector" ratio="12">N</text>
<text x="21.2852" y="13.0048" size="2.54" layer="94" font="vector" ratio="12">DATE</text>
<text x="32.7152" y="9.1948" size="2.54" layer="94" ratio="10">&gt;LAST_DATE_TIME</text>
<text x="112.4077" y="30.4673" size="1.778" layer="94" ratio="12">2015</text>
<text x="108.7564" y="30.7848" size="1.27" layer="94" ratio="12">C</text>
<text x="5.0927" y="30.4673" size="1.9304" layer="94" ratio="12">ISSUE</text>
<text x="0.9652" y="25.0698" size="1.778" layer="94" ratio="12">DRAWN</text>
<text x="0.9652" y="16.1798" size="1.778" layer="94" ratio="12">CHECKED</text>
<text x="0.9652" y="7.2898" size="1.778" layer="94" ratio="12">DATE</text>
<text x="23.349" y="29.6735" size="3.175" layer="94" ratio="18">&gt;COMPANY</text>
<text x="21.2852" y="2.8448" size="2.54" layer="94" font="vector" ratio="12">FILE:</text>
<text x="96.8502" y="2.8448" size="2.54" layer="94" font="vector" ratio="12">PAGE:</text>
<text x="2.2352" y="20.6248" size="1.778" layer="94">&gt;DRAWN</text>
<text x="2.2352" y="11.7348" size="1.778" layer="94">&gt;CHECKED</text>
<text x="2.2352" y="2.8448" size="1.778" layer="94">&gt;DATE</text>
<text x="91.1352" y="9.1948" size="2.1844" layer="94">&gt;DRGNO</text>
<text x="113.9952" y="18.7198" size="3.81" layer="94" ratio="12">&gt;REV</text>
</symbol>
<symbol name="MICROBUILDER_GND">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
<text x="-1.524" y="-2.54" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="MICROBUILDER_FRAME_A4" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A4, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="MICROBUILDER_FRAME_A4" x="0" y="0"/>
<gate name="G$3" symbol="MICROBUILDER_FRAME_DOCFIELD" x="134.62" y="3.81"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MICROBUILDER_GND">
<description>&lt;b&gt;GND&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MICROBUILDER_GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="adafruit">
<packages>
<package name="FEATHERWING">
<wire x1="2.54" y1="0" x2="48.26" y2="0" width="0" layer="20"/>
<wire x1="48.26" y1="0" x2="50.8" y2="2.54" width="0" layer="20" curve="90"/>
<wire x1="50.8" y1="2.54" x2="50.8" y2="20.32" width="0" layer="20"/>
<wire x1="50.8" y1="20.32" x2="48.26" y2="22.86" width="0" layer="20" curve="90"/>
<wire x1="48.26" y1="22.86" x2="2.54" y2="22.86" width="0" layer="20"/>
<wire x1="2.54" y1="22.86" x2="0" y2="20.32" width="0" layer="20" curve="90"/>
<wire x1="0" y1="20.32" x2="0" y2="2.54" width="0" layer="20"/>
<wire x1="0" y1="2.54" x2="2.54" y2="0" width="0" layer="20" curve="90"/>
<hole x="48.26" y="20.32" drill="2.54"/>
<hole x="48.26" y="2.54" drill="2.54"/>
<pad name="P$1" x="2.54" y="20.32" drill="2.5" diameter="3.81"/>
<pad name="P$2" x="2.54" y="2.54" drill="2.5" diameter="3.81"/>
<pad name="28" x="16.51" y="21.59" drill="1" diameter="1.778"/>
<pad name="27" x="19.05" y="21.59" drill="1" diameter="1.778"/>
<pad name="26" x="21.59" y="21.59" drill="1" diameter="1.778"/>
<pad name="25" x="24.13" y="21.59" drill="1" diameter="1.778"/>
<pad name="24" x="26.67" y="21.59" drill="1" diameter="1.778"/>
<pad name="23" x="29.21" y="21.59" drill="1" diameter="1.778"/>
<pad name="22" x="31.75" y="21.59" drill="1" diameter="1.778"/>
<pad name="21" x="34.29" y="21.59" drill="1" diameter="1.778"/>
<pad name="20" x="36.83" y="21.59" drill="1" diameter="1.778"/>
<pad name="19" x="39.37" y="21.59" drill="1" diameter="1.778"/>
<pad name="18" x="41.91" y="21.59" drill="1" diameter="1.778"/>
<pad name="17" x="44.45" y="21.59" drill="1" diameter="1.778"/>
<pad name="5" x="16.51" y="1.27" drill="1" diameter="1.778"/>
<pad name="6" x="19.05" y="1.27" drill="1" diameter="1.778"/>
<pad name="7" x="21.59" y="1.27" drill="1" diameter="1.778"/>
<pad name="8" x="24.13" y="1.27" drill="1" diameter="1.778"/>
<pad name="9" x="26.67" y="1.27" drill="1" diameter="1.778"/>
<pad name="10" x="29.21" y="1.27" drill="1" diameter="1.778"/>
<pad name="11" x="31.75" y="1.27" drill="1" diameter="1.778"/>
<pad name="12" x="34.29" y="1.27" drill="1" diameter="1.778"/>
<pad name="13" x="36.83" y="1.27" drill="1" diameter="1.778"/>
<pad name="14" x="39.37" y="1.27" drill="1" diameter="1.778"/>
<pad name="15" x="41.91" y="1.27" drill="1" diameter="1.778"/>
<pad name="16" x="44.45" y="1.27" drill="1" diameter="1.778"/>
<pad name="4" x="13.97" y="1.27" drill="1" diameter="1.778"/>
<pad name="3" x="11.43" y="1.27" drill="1" diameter="1.778"/>
<pad name="2" x="8.89" y="1.27" drill="1" diameter="1.778"/>
<pad name="1" x="6.35" y="1.27" drill="1" diameter="1.778"/>
</package>
<package name="FEATHERWING_DIM">
<wire x1="2.54" y1="0" x2="48.26" y2="0" width="0" layer="21"/>
<wire x1="48.26" y1="0" x2="50.8" y2="2.54" width="0" layer="21" curve="90"/>
<wire x1="50.8" y1="2.54" x2="50.8" y2="20.32" width="0" layer="21"/>
<wire x1="50.8" y1="20.32" x2="48.26" y2="22.86" width="0" layer="21" curve="90"/>
<wire x1="48.26" y1="22.86" x2="2.54" y2="22.86" width="0" layer="21"/>
<wire x1="2.54" y1="22.86" x2="0" y2="20.32" width="0" layer="21" curve="90"/>
<wire x1="0" y1="20.32" x2="0" y2="13.716" width="0" layer="21"/>
<wire x1="0" y1="13.716" x2="0.508" y2="13.208" width="0" layer="21"/>
<wire x1="0.508" y1="13.208" x2="0.508" y2="9.652" width="0" layer="21"/>
<wire x1="0.508" y1="9.652" x2="0" y2="9.144" width="0" layer="21"/>
<wire x1="0" y1="9.144" x2="0" y2="2.54" width="0" layer="21"/>
<wire x1="0" y1="2.54" x2="2.54" y2="0" width="0" layer="21" curve="90"/>
<hole x="48.26" y="20.32" drill="2.54"/>
<hole x="48.26" y="2.54" drill="2.54"/>
<pad name="P$1" x="2.54" y="20.32" drill="2.5" diameter="3.81"/>
<pad name="P$2" x="2.54" y="2.54" drill="2.5" diameter="3.81"/>
<pad name="28" x="16.51" y="21.59" drill="1" diameter="1.778"/>
<pad name="27" x="19.05" y="21.59" drill="1" diameter="1.778"/>
<pad name="26" x="21.59" y="21.59" drill="1" diameter="1.778"/>
<pad name="25" x="24.13" y="21.59" drill="1" diameter="1.778"/>
<pad name="24" x="26.67" y="21.59" drill="1" diameter="1.778"/>
<pad name="23" x="29.21" y="21.59" drill="1" diameter="1.778"/>
<pad name="22" x="31.75" y="21.59" drill="1" diameter="1.778"/>
<pad name="21" x="34.29" y="21.59" drill="1" diameter="1.778"/>
<pad name="20" x="36.83" y="21.59" drill="1" diameter="1.778"/>
<pad name="19" x="39.37" y="21.59" drill="1" diameter="1.778"/>
<pad name="18" x="41.91" y="21.59" drill="1" diameter="1.778"/>
<pad name="17" x="44.45" y="21.59" drill="1" diameter="1.778"/>
<pad name="5" x="16.51" y="1.27" drill="1" diameter="1.778"/>
<pad name="6" x="19.05" y="1.27" drill="1" diameter="1.778"/>
<pad name="7" x="21.59" y="1.27" drill="1" diameter="1.778"/>
<pad name="8" x="24.13" y="1.27" drill="1" diameter="1.778"/>
<pad name="9" x="26.67" y="1.27" drill="1" diameter="1.778"/>
<pad name="10" x="29.21" y="1.27" drill="1" diameter="1.778"/>
<pad name="11" x="31.75" y="1.27" drill="1" diameter="1.778"/>
<pad name="12" x="34.29" y="1.27" drill="1" diameter="1.778"/>
<pad name="13" x="36.83" y="1.27" drill="1" diameter="1.778"/>
<pad name="14" x="39.37" y="1.27" drill="1" diameter="1.778"/>
<pad name="15" x="41.91" y="1.27" drill="1" diameter="1.778"/>
<pad name="16" x="44.45" y="1.27" drill="1" diameter="1.778"/>
<pad name="4" x="13.97" y="1.27" drill="1" diameter="1.778"/>
<pad name="3" x="11.43" y="1.27" drill="1" diameter="1.778"/>
<pad name="2" x="8.89" y="1.27" drill="1" diameter="1.778"/>
<pad name="1" x="6.35" y="1.27" drill="1" diameter="1.778"/>
</package>
<package name="EG1213">
<wire x1="-5" y1="1.9" x2="-0.7" y2="1.9" width="0.127" layer="21"/>
<wire x1="-0.7" y1="1.9" x2="0.7" y2="1.9" width="0.127" layer="21"/>
<wire x1="0.7" y1="1.9" x2="5" y2="1.9" width="0.127" layer="21"/>
<wire x1="5" y1="1.9" x2="5" y2="-1.9" width="0.127" layer="21"/>
<wire x1="5" y1="-1.9" x2="2.1" y2="-1.9" width="0.127" layer="21"/>
<wire x1="2.1" y1="-1.9" x2="1" y2="-1.9" width="0.127" layer="21"/>
<wire x1="1" y1="-1.9" x2="-1" y2="-1.9" width="0.127" layer="21"/>
<wire x1="-1" y1="-1.9" x2="-2.1" y2="-1.9" width="0.127" layer="21"/>
<wire x1="-2.1" y1="-1.9" x2="-5" y2="-1.9" width="0.127" layer="21"/>
<wire x1="-5" y1="-1.9" x2="-5" y2="1.9" width="0.127" layer="21"/>
<wire x1="-0.7" y1="1.9" x2="-0.7" y2="1.2" width="0.127" layer="21"/>
<wire x1="-0.7" y1="1.2" x2="0.7" y2="1.2" width="0.127" layer="21"/>
<wire x1="0.7" y1="1.2" x2="0.7" y2="1.9" width="0.127" layer="21"/>
<wire x1="-2.1" y1="-1.9" x2="-2.1" y2="-1.6" width="0.127" layer="21"/>
<wire x1="-2.1" y1="-1.6" x2="2.1" y2="-1.6" width="0.127" layer="21"/>
<wire x1="2.1" y1="-1.6" x2="2.1" y2="-1.9" width="0.127" layer="21"/>
<wire x1="-1" y1="-1.9" x2="-1" y2="-7" width="0.127" layer="21"/>
<wire x1="-1" y1="-7" x2="1" y2="-7" width="0.127" layer="21"/>
<wire x1="1" y1="-7" x2="1" y2="-1.9" width="0.127" layer="21"/>
<pad name="2" x="0" y="0" drill="0.7" diameter="1.4224"/>
<pad name="MT2" x="4.8" y="0" drill="1.4" diameter="2.54"/>
<pad name="MT1" x="-4.8" y="0" drill="1.4" diameter="2.54"/>
<pad name="1" x="-2" y="0" drill="0.7" diameter="1.4224"/>
<pad name="3" x="1.9" y="0" drill="0.7" diameter="1.4224"/>
<text x="-2.7" y="2.4" size="1.27" layer="21" font="vector">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="MICROSHIELD">
<wire x1="0" y1="33.02" x2="0" y2="22.86" width="0.254" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="12.7" width="0.254" layer="94"/>
<wire x1="0" y1="12.7" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="48.26" y2="0" width="0.254" layer="94"/>
<wire x1="48.26" y1="0" x2="48.26" y2="33.02" width="0.254" layer="94"/>
<wire x1="48.26" y1="33.02" x2="12.7" y2="33.02" width="0.254" layer="94"/>
<pin name="!RESET" x="5.08" y="-5.08" length="middle" direction="in" rot="R90"/>
<pin name="3V" x="7.62" y="-5.08" length="middle" direction="sup" rot="R90"/>
<pin name="AREF" x="10.16" y="-5.08" length="middle" direction="pas" rot="R90"/>
<pin name="GND" x="12.7" y="-5.08" length="middle" direction="pwr" rot="R90"/>
<pin name="GPIOA0" x="15.24" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOA1" x="17.78" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOA2" x="20.32" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOA3" x="22.86" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOA4" x="25.4" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOA5" x="27.94" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOSCK" x="30.48" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOMOSI" x="33.02" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOMISO" x="35.56" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIORX" x="38.1" y="-5.08" length="middle" rot="R90"/>
<pin name="GPIOTX" x="40.64" y="-5.08" length="middle" rot="R90"/>
<pin name="NC" x="43.18" y="-5.08" length="middle" direction="pas" rot="R90"/>
<pin name="GPIOSDA" x="43.18" y="38.1" length="middle" rot="R270"/>
<pin name="GPIOSCL" x="40.64" y="38.1" length="middle" rot="R270"/>
<circle x="45.72" y="30.48" radius="1.27" width="0.254" layer="94"/>
<circle x="45.72" y="2.54" radius="1.27" width="0.254" layer="94"/>
<pin name="GPIO5" x="38.1" y="38.1" length="middle" rot="R270"/>
<pin name="GPIO9" x="33.02" y="38.1" length="middle" rot="R270"/>
<pin name="GPIO6" x="35.56" y="38.1" length="middle" rot="R270"/>
<pin name="GPIO10" x="30.48" y="38.1" length="middle" rot="R270"/>
<pin name="GPIO11" x="27.94" y="38.1" length="middle" rot="R270"/>
<pin name="GPIO12" x="25.4" y="38.1" length="middle" rot="R270"/>
<pin name="GPIO13" x="22.86" y="38.1" length="middle" rot="R270"/>
<pin name="EN" x="17.78" y="38.1" length="middle" direction="pas" rot="R270"/>
<pin name="USB" x="20.32" y="38.1" length="middle" direction="sup" rot="R270"/>
<pin name="VBAT" x="15.24" y="38.1" length="middle" direction="sup" rot="R270"/>
<wire x1="12.7" y1="33.02" x2="5.08" y2="33.02" width="0.254" layer="94"/>
<wire x1="5.08" y1="33.02" x2="0" y2="33.02" width="0.254" layer="94"/>
<wire x1="5.08" y1="33.02" x2="5.08" y2="25.4" width="0.254" layer="94"/>
<wire x1="5.08" y1="25.4" x2="7.62" y2="25.4" width="0.254" layer="94"/>
<wire x1="7.62" y1="25.4" x2="10.16" y2="25.4" width="0.254" layer="94"/>
<wire x1="10.16" y1="25.4" x2="12.7" y2="25.4" width="0.254" layer="94"/>
<wire x1="12.7" y1="25.4" x2="12.7" y2="33.02" width="0.254" layer="94"/>
<wire x1="7.62" y1="27.94" x2="7.62" y2="25.4" width="0.254" layer="94"/>
<wire x1="10.16" y1="27.94" x2="10.16" y2="25.4" width="0.254" layer="94"/>
<wire x1="0" y1="22.86" x2="5.08" y2="22.86" width="0.254" layer="94"/>
<wire x1="5.08" y1="22.86" x2="5.08" y2="12.7" width="0.254" layer="94"/>
<wire x1="5.08" y1="12.7" x2="0" y2="12.7" width="0.254" layer="94"/>
<circle x="2.54" y="2.54" radius="1.27" width="0.254" layer="94"/>
<circle x="2.54" y="30.48" radius="1.27" width="0.254" layer="94"/>
</symbol>
<symbol name="TSU">
<wire x1="0" y1="-3.175" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.905" y2="3.175" width="0.254" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="3.175" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="3.175" width="0.254" layer="94"/>
<wire x1="-0.889" y1="0" x2="-1.27" y2="0" width="0.1524" layer="94"/>
<wire x1="-1.905" y1="0" x2="-2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-3.175" y1="0" x2="-3.81" y2="0" width="0.1524" layer="94"/>
<wire x1="-6.35" y1="1.905" x2="-5.08" y2="1.905" width="0.254" layer="94"/>
<wire x1="-6.35" y1="1.905" x2="-6.35" y2="0" width="0.254" layer="94"/>
<wire x1="-6.35" y1="-1.905" x2="-5.08" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-6.35" y1="0" x2="-4.445" y2="0" width="0.1524" layer="94"/>
<wire x1="-6.35" y1="0" x2="-6.35" y2="-1.905" width="0.254" layer="94"/>
<text x="-8.255" y="-1.905" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="-5.715" y="2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="P" x="0" y="-5.08" visible="pad" length="short" direction="pas" rot="R90"/>
<pin name="S" x="2.54" y="5.08" visible="pad" length="short" direction="pas" rot="R270"/>
<pin name="O" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" rot="R270"/>
</symbol>
<symbol name="MT">
<pin name="MT" x="0" y="0" length="middle" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="FEATHERWING" prefix="MS">
<gates>
<gate name="G$1" symbol="MICROSHIELD" x="-25.4" y="-15.24"/>
</gates>
<devices>
<device name="" package="FEATHERWING">
<connects>
<connect gate="G$1" pin="!RESET" pad="1"/>
<connect gate="G$1" pin="3V" pad="2"/>
<connect gate="G$1" pin="AREF" pad="3"/>
<connect gate="G$1" pin="EN" pad="27"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="GPIO10" pad="22"/>
<connect gate="G$1" pin="GPIO11" pad="23"/>
<connect gate="G$1" pin="GPIO12" pad="24"/>
<connect gate="G$1" pin="GPIO13" pad="25"/>
<connect gate="G$1" pin="GPIO5" pad="19"/>
<connect gate="G$1" pin="GPIO6" pad="20"/>
<connect gate="G$1" pin="GPIO9" pad="21"/>
<connect gate="G$1" pin="GPIOA0" pad="5"/>
<connect gate="G$1" pin="GPIOA1" pad="6"/>
<connect gate="G$1" pin="GPIOA2" pad="7"/>
<connect gate="G$1" pin="GPIOA3" pad="8"/>
<connect gate="G$1" pin="GPIOA4" pad="9"/>
<connect gate="G$1" pin="GPIOA5" pad="10"/>
<connect gate="G$1" pin="GPIOMISO" pad="13"/>
<connect gate="G$1" pin="GPIOMOSI" pad="12"/>
<connect gate="G$1" pin="GPIORX" pad="14"/>
<connect gate="G$1" pin="GPIOSCK" pad="11"/>
<connect gate="G$1" pin="GPIOSCL" pad="18"/>
<connect gate="G$1" pin="GPIOSDA" pad="17"/>
<connect gate="G$1" pin="GPIOTX" pad="15"/>
<connect gate="G$1" pin="NC" pad="16"/>
<connect gate="G$1" pin="USB" pad="26"/>
<connect gate="G$1" pin="VBAT" pad="28"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_NODIM" package="FEATHERWING_DIM">
<connects>
<connect gate="G$1" pin="!RESET" pad="1"/>
<connect gate="G$1" pin="3V" pad="2"/>
<connect gate="G$1" pin="AREF" pad="3"/>
<connect gate="G$1" pin="EN" pad="27"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="GPIO10" pad="22"/>
<connect gate="G$1" pin="GPIO11" pad="23"/>
<connect gate="G$1" pin="GPIO12" pad="24"/>
<connect gate="G$1" pin="GPIO13" pad="25"/>
<connect gate="G$1" pin="GPIO5" pad="19"/>
<connect gate="G$1" pin="GPIO6" pad="20"/>
<connect gate="G$1" pin="GPIO9" pad="21"/>
<connect gate="G$1" pin="GPIOA0" pad="5"/>
<connect gate="G$1" pin="GPIOA1" pad="6"/>
<connect gate="G$1" pin="GPIOA2" pad="7"/>
<connect gate="G$1" pin="GPIOA3" pad="8"/>
<connect gate="G$1" pin="GPIOA4" pad="9"/>
<connect gate="G$1" pin="GPIOA5" pad="10"/>
<connect gate="G$1" pin="GPIOMISO" pad="13"/>
<connect gate="G$1" pin="GPIOMOSI" pad="12"/>
<connect gate="G$1" pin="GPIORX" pad="14"/>
<connect gate="G$1" pin="GPIOSCK" pad="11"/>
<connect gate="G$1" pin="GPIOSCL" pad="18"/>
<connect gate="G$1" pin="GPIOSDA" pad="17"/>
<connect gate="G$1" pin="GPIOTX" pad="15"/>
<connect gate="G$1" pin="NC" pad="16"/>
<connect gate="G$1" pin="USB" pad="26"/>
<connect gate="G$1" pin="VBAT" pad="28"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="EG1213" prefix="S">
<description>&lt;b&gt;E-Switch right-angle slide SPDT&lt;/b&gt; Part #EG1213
&lt;p&gt;http://www.ladyada.net/library/eagle&lt;/p&gt;</description>
<gates>
<gate name="1" symbol="TSU" x="0" y="0"/>
<gate name="G$1" symbol="MT" x="-7.62" y="-10.16"/>
<gate name="G$2" symbol="MT" x="-7.62" y="-12.7"/>
</gates>
<devices>
<device name="" package="EG1213">
<connects>
<connect gate="1" pin="O" pad="1"/>
<connect gate="1" pin="P" pad="2"/>
<connect gate="1" pin="S" pad="3"/>
<connect gate="G$1" pin="MT" pad="MT1"/>
<connect gate="G$2" pin="MT" pad="MT2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="adafruit oled featherwing">
<description>Generated from &lt;b&gt;adafruit oled featherwing.sch&lt;/b&gt;&lt;p&gt;
by exp-lbrs.ulp</description>
<packages>
<package name="MICROBUILDER_EVQ-Q2">
<circle x="0" y="0" radius="1.5033" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="1" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3" x2="3.3" y2="3" width="0.2032" layer="21"/>
<wire x1="3.3" y1="3" x2="3.3" y2="-3" width="0.127" layer="51"/>
<wire x1="3.3" y1="-3" x2="-3.3" y2="-3" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="-3" x2="-3.3" y2="3" width="0.127" layer="51"/>
<wire x1="-3.3" y1="-1.2" x2="-3.3" y2="1.2" width="0.2032" layer="21"/>
<wire x1="3.3" y1="1.2" x2="3.3" y2="-1.2" width="0.2032" layer="21"/>
<smd name="A" x="-3.4" y="-2" dx="3.2" dy="1.2" layer="1"/>
<smd name="A'" x="3.4" y="-2" dx="3.2" dy="1.2" layer="1"/>
<smd name="B" x="-3.4" y="2" dx="3.2" dy="1.2" layer="1"/>
<smd name="B'" x="3.4" y="2" dx="3.2" dy="1.2" layer="1"/>
<text x="-3.175" y="3.5" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-3.175" y="-3.683" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_BTN_KMR2_4.6X2.8">
<wire x1="-0.4" y1="0.4" x2="0" y2="0.4" width="0.127" layer="51"/>
<wire x1="0" y1="0.4" x2="0.4" y2="0.4" width="0.127" layer="51"/>
<wire x1="-0.4" y1="-0.4" x2="0" y2="-0.4" width="0.127" layer="51"/>
<wire x1="0" y1="-0.4" x2="0.4" y2="-0.4" width="0.127" layer="51"/>
<wire x1="0" y1="0.4" x2="0" y2="0.2" width="0.127" layer="51"/>
<wire x1="0" y1="-0.4" x2="0" y2="-0.3" width="0.127" layer="51"/>
<wire x1="0" y1="0.2" x2="0.3" y2="-0.1" width="0.127" layer="51"/>
<wire x1="-2.1" y1="1.4" x2="2.1" y2="1.4" width="0.2032" layer="51"/>
<wire x1="2.1" y1="1.4" x2="2.1" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="2.1" y1="-1.4" x2="-2.1" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-2.1" y1="-1.4" x2="-2.1" y2="1.4" width="0.2032" layer="51"/>
<wire x1="-1.05" y1="-0.8" x2="-1.05" y2="0.8" width="0.2032" layer="51" curve="-44.999389"/>
<wire x1="-1.05" y1="0.8" x2="1.05" y2="0.8" width="0.2032" layer="51"/>
<wire x1="1.05" y1="0.8" x2="1.05" y2="-0.8" width="0.2032" layer="51" curve="-44.999389"/>
<wire x1="1.05" y1="-0.8" x2="-1.05" y2="-0.8" width="0.2032" layer="51"/>
<wire x1="-2.1" y1="1.5254" x2="2.1" y2="1.5254" width="0.2032" layer="21"/>
<wire x1="2.1" y1="-1.5254" x2="-2.1" y2="-1.5254" width="0.2032" layer="21"/>
<smd name="A" x="2.05" y="0.8" dx="0.9" dy="1" layer="1"/>
<smd name="A'" x="-2.05" y="0.8" dx="0.9" dy="1" layer="1"/>
<smd name="B" x="2.05" y="-0.8" dx="0.9" dy="1" layer="1"/>
<smd name="B'" x="-2.05" y="-0.8" dx="0.9" dy="1" layer="1"/>
<text x="-2.032" y="1.778" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-2.032" y="-2.159" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_BTN_EVQPQ_4.5MM">
<circle x="0" y="0" radius="2.15" width="0.2032" layer="51"/>
<wire x1="-2.25" y1="2.25" x2="2.25" y2="2.25" width="0.127" layer="51"/>
<wire x1="2.25" y1="2.25" x2="2.25" y2="-2.25" width="0.127" layer="51"/>
<wire x1="2.25" y1="-2.25" x2="-2.25" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-2.25" y1="-2.25" x2="-2.25" y2="2.25" width="0.127" layer="51"/>
<wire x1="-2.25" y1="-1.15" x2="-2.25" y2="1.15" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="2.25" x2="1.25" y2="2.25" width="0.2032" layer="21"/>
<wire x1="2.25" y1="1.15" x2="2.25" y2="-1.15" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="-2.25" x2="1.25" y2="-2.25" width="0.2032" layer="21"/>
<smd name="A" x="-1.95" y="1.925" dx="0.9" dy="1" layer="1"/>
<smd name="B" x="1.95" y="1.925" dx="0.9" dy="1" layer="1"/>
<smd name="C" x="-1.95" y="-1.925" dx="0.9" dy="1" layer="1"/>
<smd name="D" x="1.95" y="-1.925" dx="0.9" dy="1" layer="1"/>
<text x="-2.286" y="2.794" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-2.286" y="-3.556" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_BTN_KMT0">
<description>&lt;p&gt;Source: http://media.digikey.com/pdf/Data%20Sheets/C&amp;K/KMT_0xx_NGJ_LHS_Drawing.pdf&lt;/p&gt;</description>
<circle x="0" y="0" radius="0.391309375" width="0.05" layer="51"/>
<circle x="0" y="0" radius="1.053859375" width="0.05" layer="51"/>
<wire x1="-1.15" y1="1.3" x2="-1.25" y2="1.2" width="0.05" layer="51" curve="90"/>
<wire x1="-1.25" y1="1.2" x2="-1.25" y2="0.7" width="0.05" layer="51"/>
<wire x1="-1.25" y1="0.7" x2="-1.4" y2="0.55" width="0.05" layer="51" curve="-90"/>
<wire x1="-1.4" y1="0.55" x2="-1.425" y2="0.55" width="0.05" layer="51"/>
<wire x1="-1.425" y1="0.55" x2="-1.5" y2="0.475" width="0.05" layer="51" curve="90"/>
<wire x1="-1.5" y1="0.475" x2="-1.5" y2="0.15" width="0.05" layer="51"/>
<wire x1="-1.5" y1="0.15" x2="-1.5" y2="-0.25" width="0.05" layer="51"/>
<wire x1="-1.5" y1="-0.25" x2="-1.5" y2="-0.5" width="0.05" layer="51"/>
<wire x1="-1.5" y1="-0.5" x2="-1.425" y2="-0.575" width="0.05" layer="51" curve="90"/>
<wire x1="-1.425" y1="-0.575" x2="-1.4" y2="-0.575" width="0.05" layer="51"/>
<wire x1="-1.4" y1="-0.575" x2="-1.25" y2="-0.725" width="0.05" layer="51" curve="-90"/>
<wire x1="-1.25" y1="-0.725" x2="-1.25" y2="-1.2" width="0.05" layer="51"/>
<wire x1="-1.25" y1="-1.2" x2="-1.125" y2="-1.325" width="0.05" layer="51" curve="90"/>
<wire x1="-1.125" y1="-1.325" x2="1.125" y2="-1.325" width="0.05" layer="51"/>
<wire x1="1.125" y1="-1.325" x2="1.25" y2="-1.2" width="0.05" layer="51" curve="90"/>
<wire x1="1.25" y1="-1.2" x2="1.25" y2="-0.7" width="0.05" layer="51"/>
<wire x1="1.25" y1="-0.7" x2="1.375" y2="-0.575" width="0.05" layer="51" curve="-90"/>
<wire x1="1.375" y1="-0.575" x2="1.425" y2="-0.575" width="0.05" layer="51"/>
<wire x1="1.425" y1="-0.575" x2="1.5" y2="-0.5" width="0.05" layer="51" curve="90"/>
<wire x1="1.5" y1="-0.5" x2="1.5" y2="-0.275" width="0.05" layer="51"/>
<wire x1="1.5" y1="-0.275" x2="1.5" y2="0.125" width="0.05" layer="51"/>
<wire x1="1.5" y1="0.125" x2="1.5" y2="0.475" width="0.05" layer="51"/>
<wire x1="1.5" y1="0.475" x2="1.425" y2="0.55" width="0.05" layer="51" curve="90"/>
<wire x1="1.4" y1="0.55" x2="1.35" y2="0.55" width="0.05" layer="51"/>
<wire x1="1.35" y1="0.55" x2="1.25" y2="0.65" width="0.05" layer="51" curve="-90"/>
<wire x1="1.25" y1="0.65" x2="1.25" y2="1.2" width="0.05" layer="51"/>
<wire x1="1.25" y1="1.2" x2="1.15" y2="1.3" width="0.05" layer="51" curve="90"/>
<wire x1="1.15" y1="1.3" x2="-1.15" y2="1.3" width="0.05" layer="51"/>
<wire x1="1.15" y1="1.3" x2="1.25" y2="1.3" width="0.05" layer="51"/>
<wire x1="1.25" y1="1.3" x2="1.375" y2="1.175" width="0.05" layer="51" curve="-90"/>
<wire x1="1.375" y1="1.175" x2="1.325" y2="1.175" width="0.05" layer="51"/>
<wire x1="1.325" y1="1.175" x2="1.325" y2="0.675" width="0.05" layer="51"/>
<wire x1="1.325" y1="0.675" x2="1.325" y2="0.625" width="0.05" layer="51"/>
<wire x1="1.325" y1="0.625" x2="1.4" y2="0.55" width="0.05" layer="51" curve="90"/>
<wire x1="1.4" y1="0.55" x2="1.425" y2="0.55" width="0.05" layer="51"/>
<wire x1="1.425" y1="0.55" x2="1.5" y2="0.475" width="0.05" layer="51" curve="-90"/>
<wire x1="1.5" y1="0.125" x2="1.55" y2="0.125" width="0.05" layer="51"/>
<wire x1="1.55" y1="0.125" x2="1.55" y2="-0.275" width="0.05" layer="51"/>
<wire x1="1.55" y1="-0.275" x2="1.5" y2="-0.275" width="0.05" layer="51"/>
<wire x1="1.375" y1="1.175" x2="1.625" y2="1.175" width="0.05" layer="51"/>
<wire x1="1.625" y1="1.175" x2="1.725" y2="1.175" width="0.05" layer="51"/>
<wire x1="1.725" y1="1.175" x2="1.725" y2="0.675" width="0.05" layer="51"/>
<wire x1="1.725" y1="0.675" x2="1.625" y2="0.675" width="0.05" layer="51"/>
<wire x1="1.625" y1="0.675" x2="1.5" y2="0.675" width="0.05" layer="51"/>
<wire x1="1.5" y1="0.675" x2="1.325" y2="0.675" width="0.05" layer="51"/>
<wire x1="1.5" y1="0.475" x2="1.5" y2="0.675" width="0.05" layer="51"/>
<wire x1="1.625" y1="1.175" x2="1.625" y2="0.675" width="0.05" layer="51"/>
<wire x1="1.325" y1="-0.725" x2="1.325" y2="-0.675" width="0.05" layer="51"/>
<wire x1="1.325" y1="-0.675" x2="1.425" y2="-0.575" width="0.05" layer="51" curve="-90"/>
<wire x1="1.325" y1="-0.725" x2="1.5" y2="-0.725" width="0.05" layer="51"/>
<wire x1="1.5" y1="-0.725" x2="1.6" y2="-0.725" width="0.05" layer="51"/>
<wire x1="1.6" y1="-0.725" x2="1.7" y2="-0.725" width="0.05" layer="51"/>
<wire x1="1.7" y1="-0.725" x2="1.7" y2="-1.225" width="0.05" layer="51"/>
<wire x1="1.7" y1="-1.225" x2="1.6" y2="-1.225" width="0.05" layer="51"/>
<wire x1="1.6" y1="-1.225" x2="1.375" y2="-1.225" width="0.05" layer="51"/>
<wire x1="1.375" y1="-1.225" x2="1.325" y2="-1.225" width="0.05" layer="51"/>
<wire x1="1.325" y1="-1.225" x2="1.325" y2="-0.725" width="0.05" layer="51"/>
<wire x1="1.6" y1="-0.725" x2="1.6" y2="-1.225" width="0.05" layer="51"/>
<wire x1="1.125" y1="-1.325" x2="1.275" y2="-1.325" width="0.05" layer="51"/>
<wire x1="1.275" y1="-1.325" x2="1.375" y2="-1.225" width="0.05" layer="51" curve="90"/>
<wire x1="1.5" y1="-0.5" x2="1.5" y2="-0.725" width="0.05" layer="51"/>
<wire x1="-1.05" y1="1.225" x2="1.05" y2="1.225" width="0.05" layer="51"/>
<wire x1="1.05" y1="1.225" x2="1.175" y2="1.1" width="0.05" layer="51" curve="-90"/>
<wire x1="1.175" y1="1.1" x2="1.175" y2="0.675" width="0.05" layer="51"/>
<wire x1="1.175" y1="0.675" x2="1.325" y2="0.525" width="0.05" layer="51" curve="90"/>
<wire x1="1.325" y1="0.525" x2="1.35" y2="0.525" width="0.05" layer="51"/>
<wire x1="1.35" y1="0.525" x2="1.45" y2="0.425" width="0.05" layer="51" curve="-90"/>
<wire x1="1.45" y1="0.425" x2="1.45" y2="-0.45" width="0.05" layer="51"/>
<wire x1="1.45" y1="-0.45" x2="1.325" y2="-0.575" width="0.05" layer="51" curve="-90"/>
<wire x1="1.325" y1="-0.575" x2="1.3" y2="-0.575" width="0.05" layer="51"/>
<wire x1="1.3" y1="-0.575" x2="1.175" y2="-0.7" width="0.05" layer="51" curve="90"/>
<wire x1="1.175" y1="-0.7" x2="1.175" y2="-1.125" width="0.05" layer="51"/>
<wire x1="1.175" y1="-1.125" x2="1.05" y2="-1.25" width="0.05" layer="51" curve="-90"/>
<wire x1="1.05" y1="-1.25" x2="-1.025" y2="-1.25" width="0.05" layer="51"/>
<wire x1="-1.025" y1="-1.25" x2="-1.175" y2="-1.1" width="0.05" layer="51" curve="-90"/>
<wire x1="-1.175" y1="-1.1" x2="-1.175" y2="-0.725" width="0.05" layer="51"/>
<wire x1="-1.175" y1="-0.725" x2="-1.35" y2="-0.55" width="0.05" layer="51" curve="90"/>
<wire x1="-1.35" y1="-0.55" x2="-1.375" y2="-0.55" width="0.05" layer="51"/>
<wire x1="-1.375" y1="-0.55" x2="-1.45" y2="-0.475" width="0.05" layer="51" curve="-90"/>
<wire x1="-1.45" y1="-0.475" x2="-1.45" y2="0.425" width="0.05" layer="51"/>
<wire x1="-1.45" y1="0.425" x2="-1.35" y2="0.525" width="0.05" layer="51" curve="-90"/>
<wire x1="-1.35" y1="0.525" x2="-1.325" y2="0.525" width="0.05" layer="51"/>
<wire x1="-1.325" y1="0.525" x2="-1.175" y2="0.675" width="0.05" layer="51" curve="90"/>
<wire x1="-1.175" y1="0.675" x2="-1.175" y2="1.1" width="0.05" layer="51"/>
<wire x1="-1.175" y1="1.1" x2="-1.05" y2="1.225" width="0.05" layer="51" curve="-90"/>
<wire x1="-1.15" y1="1.3" x2="-1.275" y2="1.3" width="0.05" layer="51"/>
<wire x1="-1.275" y1="1.3" x2="-1.375" y2="1.2" width="0.05" layer="51" curve="90"/>
<wire x1="-1.7" y1="1.2" x2="-1.6" y2="1.2" width="0.05" layer="51"/>
<wire x1="-1.6" y1="1.2" x2="-1.35" y2="1.2" width="0.05" layer="51"/>
<wire x1="-1.35" y1="1.2" x2="-1.35" y2="0.7" width="0.05" layer="51"/>
<wire x1="-1.35" y1="0.7" x2="-1.5" y2="0.7" width="0.05" layer="51"/>
<wire x1="-1.5" y1="0.7" x2="-1.6" y2="0.7" width="0.05" layer="51"/>
<wire x1="-1.6" y1="0.7" x2="-1.7" y2="0.7" width="0.05" layer="51"/>
<wire x1="-1.7" y1="0.7" x2="-1.7" y2="1.2" width="0.05" layer="51"/>
<wire x1="-1.6" y1="1.2" x2="-1.6" y2="0.7" width="0.05" layer="51"/>
<wire x1="-1.35" y1="0.7" x2="-1.35" y2="0.625" width="0.05" layer="51"/>
<wire x1="-1.35" y1="0.625" x2="-1.425" y2="0.55" width="0.05" layer="51" curve="-90"/>
<wire x1="-1.5" y1="0.15" x2="-1.55" y2="0.15" width="0.05" layer="51"/>
<wire x1="-1.55" y1="0.15" x2="-1.55" y2="-0.25" width="0.05" layer="51"/>
<wire x1="-1.55" y1="-0.25" x2="-1.5" y2="-0.25" width="0.05" layer="51"/>
<wire x1="-1.5" y1="0.475" x2="-1.5" y2="0.7" width="0.05" layer="51"/>
<wire x1="-1.125" y1="-1.325" x2="-1.275" y2="-1.325" width="0.05" layer="51"/>
<wire x1="-1.275" y1="-1.325" x2="-1.375" y2="-1.225" width="0.05" layer="51" curve="-90"/>
<wire x1="-1.25" y1="-1.225" x2="-1.35" y2="-1.225" width="0.05" layer="51"/>
<wire x1="-1.35" y1="-1.225" x2="-1.625" y2="-1.225" width="0.05" layer="51"/>
<wire x1="-1.625" y1="-1.225" x2="-1.725" y2="-1.225" width="0.05" layer="51"/>
<wire x1="-1.725" y1="-1.225" x2="-1.725" y2="-0.725" width="0.05" layer="51"/>
<wire x1="-1.725" y1="-0.725" x2="-1.625" y2="-0.725" width="0.05" layer="51"/>
<wire x1="-1.625" y1="-0.725" x2="-1.5" y2="-0.725" width="0.05" layer="51"/>
<wire x1="-1.5" y1="-0.725" x2="-1.35" y2="-0.725" width="0.05" layer="51"/>
<wire x1="-1.35" y1="-0.725" x2="-1.35" y2="-1.225" width="0.05" layer="51"/>
<wire x1="-1.625" y1="-0.725" x2="-1.625" y2="-1.225" width="0.05" layer="51"/>
<wire x1="-1.35" y1="-0.725" x2="-1.35" y2="-0.65" width="0.05" layer="51"/>
<wire x1="-1.35" y1="-0.65" x2="-1.425" y2="-0.575" width="0.05" layer="51" curve="90"/>
<wire x1="-1.5" y1="-0.5" x2="-1.5" y2="-0.725" width="0.05" layer="51"/>
<wire x1="-0.975" y1="1.3" x2="0.975" y2="1.3" width="0.05" layer="21"/>
<wire x1="-1.5" y1="0.475" x2="-1.5" y2="-0.475" width="0.05" layer="21"/>
<wire x1="1.5" y1="0.475" x2="1.5" y2="-0.475" width="0.05" layer="21"/>
<wire x1="-0.975" y1="-1.325" x2="0.975" y2="-1.325" width="0.05" layer="21"/>
<smd name="A" x="-1.625" y="0.95" dx="0.95" dy="0.7" layer="1"/>
<smd name="A'" x="1.625" y="0.95" dx="0.95" dy="0.7" layer="1"/>
<smd name="B" x="-1.625" y="-0.95" dx="0.95" dy="0.7" layer="1"/>
<smd name="B'" x="1.625" y="-0.95" dx="0.95" dy="0.7" layer="1"/>
<text x="-1.732" y="1.503" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-1.507" y="-1.884" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_0603-MINI">
<description>0603-Mini
&lt;p&gt;Mini footprint for dense boards&lt;/p&gt;</description>
<wire x1="-1.346" y1="0.583" x2="1.346" y2="0.583" width="0.0508" layer="39"/>
<wire x1="1.346" y1="0.583" x2="1.346" y2="-0.583" width="0.0508" layer="39"/>
<wire x1="1.346" y1="-0.583" x2="-1.346" y2="-0.583" width="0.0508" layer="39"/>
<wire x1="-1.346" y1="-0.583" x2="-1.346" y2="0.583" width="0.0508" layer="39"/>
<wire x1="-1.45" y1="-0.7" x2="-1.45" y2="0.7" width="0.2032" layer="21"/>
<wire x1="-1.45" y1="0.7" x2="1.45" y2="0.7" width="0.2032" layer="21"/>
<wire x1="1.45" y1="0.7" x2="1.45" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="1.45" y1="-0.7" x2="-1.45" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<smd name="1" x="-0.75" y="0" dx="0.9" dy="0.9" layer="1"/>
<smd name="2" x="0.75" y="0" dx="0.9" dy="0.9" layer="1"/>
<text x="1.524" y="-0.0635" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="1.524" y="-0.635" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_0805-NO">
<wire x1="-0.381" y1="0.66" x2="0.381" y2="0.66" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.66" x2="0.381" y2="-0.66" width="0.1016" layer="51"/>
<wire x1="0" y1="0.508" x2="0" y2="-0.508" width="0.3048" layer="21"/>
<rectangle x1="-1.0922" y1="-0.7239" x2="-0.3421" y2="0.7262" layer="51"/>
<rectangle x1="0.3556" y1="-0.7239" x2="1.1057" y2="0.7262" layer="51"/>
<smd name="1" x="-0.95" y="0" dx="1.3" dy="1.5" layer="1"/>
<smd name="2" x="0.95" y="0" dx="1.3" dy="1.5" layer="1"/>
<text x="2.032" y="-0.127" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="2.032" y="-0.762" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_0805_NOTHERMALS">
<wire x1="-1.873" y1="0.883" x2="1.873" y2="0.883" width="0.0508" layer="39"/>
<wire x1="1.873" y1="-0.883" x2="-1.873" y2="-0.883" width="0.0508" layer="39"/>
<wire x1="-1.873" y1="-0.883" x2="-1.873" y2="0.883" width="0.0508" layer="39"/>
<wire x1="-0.381" y1="0.66" x2="0.381" y2="0.66" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.66" x2="0.381" y2="-0.66" width="0.1016" layer="51"/>
<wire x1="1.873" y1="0.883" x2="1.873" y2="-0.883" width="0.0508" layer="39"/>
<wire x1="1.85" y1="1" x2="1.85" y2="-1" width="0.2032" layer="21"/>
<wire x1="1.85" y1="-1" x2="-1.85" y2="-1" width="0.2032" layer="21"/>
<wire x1="-1.85" y1="-1" x2="-1.85" y2="1" width="0.2032" layer="21"/>
<wire x1="-1.85" y1="1" x2="1.85" y2="1" width="0.2032" layer="21"/>
<rectangle x1="-1.0922" y1="-0.7239" x2="-0.3421" y2="0.7262" layer="51"/>
<rectangle x1="0.3556" y1="-0.7239" x2="1.1057" y2="0.7262" layer="51"/>
<smd name="1" x="-0.95" y="0" dx="1.3" dy="1.5" layer="1" thermals="no"/>
<smd name="2" x="0.95" y="0" dx="1.3" dy="1.5" layer="1" thermals="no"/>
<text x="2.032" y="-0.127" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="2.032" y="-0.762" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_2012">
<wire x1="-1.662" y1="1.245" x2="1.662" y2="1.245" width="0.2032" layer="51"/>
<wire x1="-1.637" y1="-1.245" x2="1.687" y2="-1.245" width="0.2032" layer="51"/>
<wire x1="-3.473" y1="1.483" x2="3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="1.483" x2="3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-1.483" x2="-3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-1.483" x2="-3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="-3.302" y1="1.524" x2="3.302" y2="1.524" width="0.2032" layer="21"/>
<wire x1="3.302" y1="1.524" x2="3.302" y2="-1.524" width="0.2032" layer="21"/>
<wire x1="3.302" y1="-1.524" x2="-3.302" y2="-1.524" width="0.2032" layer="21"/>
<wire x1="-3.302" y1="-1.524" x2="-3.302" y2="1.524" width="0.2032" layer="21"/>
<rectangle x1="-2.4892" y1="-1.3208" x2="-1.6393" y2="1.3292" layer="51"/>
<rectangle x1="1.651" y1="-1.3208" x2="2.5009" y2="1.3292" layer="51"/>
<smd name="1" x="-2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<smd name="2" x="2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<text x="-2.54" y="1.8415" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-2.667" y="-2.159" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_2512">
<description>&lt;b&gt;RESISTOR 2512 (Metric 6432)&lt;/b&gt;</description>
<wire x1="-2.362" y1="1.473" x2="2.387" y2="1.473" width="0.2032" layer="51"/>
<wire x1="-2.362" y1="-1.473" x2="2.387" y2="-1.473" width="0.2032" layer="51"/>
<wire x1="-3.973" y1="1.983" x2="3.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="1.983" x2="3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="3.973" y1="-1.983" x2="-3.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-3.973" y1="-1.983" x2="-3.973" y2="1.983" width="0.0508" layer="39"/>
<rectangle x1="-3.2004" y1="-1.5494" x2="-2.3505" y2="1.5507" layer="51"/>
<rectangle x1="2.3622" y1="-1.5494" x2="3.2121" y2="1.5507" layer="51"/>
<rectangle x1="-0.5001" y1="-1" x2="0.5001" y2="1" layer="35"/>
<smd name="1" x="-2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<smd name="2" x="2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<text x="-3.683" y="1.905" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-3.556" y="-2.286" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER__0402">
<description>&lt;b&gt; 0402&lt;/b&gt;</description>
<wire x1="-0.245" y1="0.174" x2="0.245" y2="0.174" width="0.1016" layer="51"/>
<wire x1="0.245" y1="-0.174" x2="-0.245" y2="-0.174" width="0.1016" layer="51"/>
<wire x1="-1.0573" y1="0.5557" x2="1.0573" y2="0.5557" width="0.2032" layer="21"/>
<wire x1="1.0573" y1="0.5557" x2="1.0573" y2="-0.5556" width="0.2032" layer="21"/>
<wire x1="1.0573" y1="-0.5556" x2="-1.0573" y2="-0.5557" width="0.2032" layer="21"/>
<wire x1="-1.0573" y1="-0.5557" x2="-1.0573" y2="0.5557" width="0.2032" layer="21"/>
<rectangle x1="-0.0794" y1="-0.2381" x2="0.0794" y2="0.2381" layer="35"/>
<rectangle x1="0.25" y1="-0.25" x2="0.5" y2="0.25" layer="51"/>
<rectangle x1="-0.5" y1="-0.25" x2="-0.25" y2="0.25" layer="51"/>
<smd name="1" x="-0.508" y="0" dx="0.6" dy="0.6" layer="1"/>
<smd name="2" x="0.508" y="0" dx="0.6" dy="0.6" layer="1"/>
<text x="-0.9525" y="0.7939" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-0.9525" y="-1.3336" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER__0402MP">
<description>&lt;b&gt;0402 MicroPitch&lt;p&gt;</description>
<wire x1="-0.245" y1="0.174" x2="0.245" y2="0.174" width="0.1016" layer="51"/>
<wire x1="0.245" y1="-0.174" x2="-0.245" y2="-0.174" width="0.1016" layer="51"/>
<wire x1="0" y1="0.127" x2="0" y2="-0.127" width="0.2032" layer="21"/>
<rectangle x1="-0.1" y1="-0.2" x2="0.1" y2="0.2" layer="35"/>
<rectangle x1="-0.5" y1="-0.25" x2="-0.254" y2="0.25" layer="51"/>
<rectangle x1="0.2588" y1="-0.25" x2="0.5" y2="0.25" layer="51"/>
<smd name="1" x="-0.508" y="0" dx="0.5" dy="0.5" layer="1"/>
<smd name="2" x="0.508" y="0" dx="0.5" dy="0.5" layer="1"/>
<text x="-0.635" y="0.4763" size="0.6096" layer="25" ratio="18">&gt;NAME</text>
<text x="-0.635" y="-0.7938" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER__0603">
<description>&lt;b&gt;0603&lt;/b&gt;</description>
<wire x1="-0.432" y1="-0.306" x2="0.432" y2="-0.306" width="0.1016" layer="51"/>
<wire x1="0.432" y1="0.306" x2="-0.432" y2="0.306" width="0.1016" layer="51"/>
<wire x1="-1.4605" y1="0.635" x2="1.4605" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.4605" y1="0.635" x2="1.4605" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="1.4605" y1="-0.635" x2="-1.4605" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.4605" y1="-0.635" x2="-1.4605" y2="0.635" width="0.2032" layer="21"/>
<rectangle x1="0.4318" y1="-0.4" x2="0.8382" y2="0.4" layer="51"/>
<rectangle x1="-0.8382" y1="-0.4" x2="-0.4318" y2="0.4" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
<smd name="1" x="-0.762" y="0" dx="0.9" dy="0.8" layer="1"/>
<smd name="2" x="0.762" y="0" dx="0.9" dy="0.8" layer="1"/>
<text x="-1.27" y="0.9525" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-1.27" y="-1.4923" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER__0603MP">
<description>&lt;b&gt;0603 MicroPitch&lt;/b&gt;</description>
<wire x1="-0.432" y1="-0.306" x2="0.432" y2="-0.306" width="0.1016" layer="51"/>
<wire x1="0.432" y1="0.306" x2="-0.432" y2="0.306" width="0.1016" layer="51"/>
<wire x1="0" y1="0.254" x2="0" y2="-0.254" width="0.2032" layer="21"/>
<rectangle x1="0.4318" y1="-0.4" x2="0.8" y2="0.4" layer="51"/>
<rectangle x1="-0.8" y1="-0.4" x2="-0.4318" y2="0.4" layer="51"/>
<rectangle x1="-0.1999" y1="-0.25" x2="0.1999" y2="0.25" layer="35"/>
<smd name="1" x="-0.762" y="0" dx="0.8" dy="0.8" layer="1"/>
<smd name="2" x="0.762" y="0" dx="0.8" dy="0.8" layer="1"/>
<text x="-0.9525" y="0.635" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-0.9525" y="-0.9525" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER_0603-NO">
<wire x1="-1.473" y1="0.729" x2="1.473" y2="0.729" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.729" x2="1.473" y2="-0.729" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.729" x2="-1.473" y2="-0.729" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.729" x2="-1.473" y2="0.729" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="1.778" y="-0.127" size="0.8128" layer="25" font="vector" ratio="18">&gt;NAME</text>
<text x="1.778" y="-0.762" size="0.4064" layer="27" font="vector" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER__0805">
<description>&lt;b&gt;0805&lt;/b&gt;</description>
<wire x1="-0.41" y1="0.585" x2="0.41" y2="0.585" width="0.1016" layer="51"/>
<wire x1="-0.41" y1="-0.585" x2="0.41" y2="-0.585" width="0.1016" layer="51"/>
<wire x1="-1.905" y1="0.889" x2="1.905" y2="0.889" width="0.2032" layer="21"/>
<wire x1="1.905" y1="0.889" x2="1.905" y2="-0.889" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-0.889" x2="-1.905" y2="-0.889" width="0.2032" layer="21"/>
<wire x1="-1.905" y1="-0.889" x2="-1.905" y2="0.889" width="0.2032" layer="21"/>
<rectangle x1="0.4064" y1="-0.65" x2="1.0564" y2="0.65" layer="51"/>
<rectangle x1="-1.0668" y1="-0.65" x2="-0.4168" y2="0.65" layer="51"/>
<rectangle x1="-0.1999" y1="-0.5001" x2="0.1999" y2="0.5001" layer="35"/>
<smd name="1" x="-1.016" y="0" dx="1.2" dy="1.3" layer="1"/>
<smd name="2" x="1.016" y="0" dx="1.2" dy="1.3" layer="1"/>
<text x="-1.5875" y="1.27" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-1.5874" y="-1.651" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER__0805MP">
<description>&lt;b&gt;0805 MicroPitch&lt;/b&gt;</description>
<wire x1="-0.51" y1="0.535" x2="0.51" y2="0.535" width="0.1016" layer="51"/>
<wire x1="-0.51" y1="-0.535" x2="0.51" y2="-0.535" width="0.1016" layer="51"/>
<wire x1="0" y1="0.508" x2="0" y2="-0.508" width="0.2032" layer="21"/>
<rectangle x1="0.4064" y1="-0.65" x2="1" y2="0.65" layer="51"/>
<rectangle x1="-1" y1="-0.65" x2="-0.4168" y2="0.65" layer="51"/>
<rectangle x1="-0.1999" y1="-0.5001" x2="0.1999" y2="0.5001" layer="35"/>
<smd name="1" x="-1.016" y="0" dx="1.2" dy="1.3" layer="1"/>
<smd name="2" x="1.016" y="0" dx="1.2" dy="1.3" layer="1"/>
<text x="-1.5875" y="0.9525" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-1.5875" y="-1.27" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER__1206">
<wire x1="0.9525" y1="-0.8128" x2="-0.9652" y2="-0.8128" width="0.1016" layer="51"/>
<wire x1="0.9525" y1="0.8128" x2="-0.9652" y2="0.8128" width="0.1016" layer="51"/>
<wire x1="-2.286" y1="1.143" x2="2.286" y2="1.143" width="0.2032" layer="21"/>
<wire x1="2.286" y1="1.143" x2="2.286" y2="-1.143" width="0.2032" layer="21"/>
<wire x1="2.286" y1="-1.143" x2="-2.286" y2="-1.143" width="0.2032" layer="21"/>
<wire x1="-2.286" y1="-1.143" x2="-2.286" y2="1.143" width="0.2032" layer="21"/>
<rectangle x1="-1.6891" y1="-0.8763" x2="-0.9525" y2="0.8763" layer="51"/>
<rectangle x1="0.9525" y1="-0.8763" x2="1.6891" y2="0.8763" layer="51"/>
<rectangle x1="-0.3" y1="-0.7" x2="0.3" y2="0.7" layer="35"/>
<smd name="1" x="-1.27" y="0" dx="1.4" dy="1.8" layer="1"/>
<smd name="2" x="1.27" y="0" dx="1.4" dy="1.8" layer="1"/>
<text x="-2.2225" y="1.5113" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-2.2225" y="-1.8288" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MICROBUILDER__1206MP">
<wire x1="1.0525" y1="-0.7128" x2="-1.0652" y2="-0.7128" width="0.1016" layer="51"/>
<wire x1="1.0525" y1="0.7128" x2="-1.0652" y2="0.7128" width="0.1016" layer="51"/>
<wire x1="-0.635" y1="0.635" x2="0.635" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="-0.635" x2="0.635" y2="-0.635" width="0.2032" layer="21"/>
<rectangle x1="-1.6" y1="-0.8" x2="-0.9" y2="0.8" layer="51"/>
<rectangle x1="-0.3" y1="-0.7" x2="0.3" y2="0.7" layer="35"/>
<rectangle x1="0.9001" y1="-0.8" x2="1.6" y2="0.8" layer="51" rot="R180"/>
<smd name="1" x="-1.524" y="0" dx="1.3" dy="1.6" layer="1"/>
<smd name="2" x="1.524" y="0" dx="1.3" dy="1.6" layer="1"/>
<text x="-2.2225" y="1.1113" size="0.8128" layer="25" ratio="18">&gt;NAME</text>
<text x="-2.2225" y="-1.4288" size="0.4064" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MICROBUILDER_BUTTON_4PIN">
<circle x="-2.54" y="0" radius="0.127" width="0.4064" layer="94"/>
<circle x="2.54" y="0" radius="0.127" width="0.4064" layer="94"/>
<wire x1="1.905" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="1.905" y1="4.445" x2="1.905" y2="3.175" width="0.254" layer="94"/>
<wire x1="-1.905" y1="4.445" x2="-1.905" y2="3.175" width="0.254" layer="94"/>
<wire x1="1.905" y1="4.445" x2="0" y2="4.445" width="0.254" layer="94"/>
<wire x1="0" y1="4.445" x2="-1.905" y2="4.445" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="94"/>
<wire x1="0" y1="4.445" x2="0" y2="3.175" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="1.905" y2="1.27" width="0.254" layer="94"/>
<pin name="P" x="-5.08" y="0" visible="pad" length="short" direction="pas" swaplevel="2"/>
<pin name="P1" x="-5.08" y="-2.54" visible="pad" length="short" direction="pas" swaplevel="2"/>
<pin name="S" x="5.08" y="0" visible="pad" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="S1" x="5.08" y="-2.54" visible="pad" length="short" direction="pas" swaplevel="1" rot="R180"/>
<text x="-2.54" y="6.35" size="1.27" layer="95">&gt;NAME</text>
<text x="-2.54" y="-5.08" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="MICROBUILDER_RESISTOR">
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.254" layer="94"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="2.54" y1="-1.27" x2="-2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="1.27" width="0.254" layer="94"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<text x="0" y="2.54" size="1.27" layer="95" font="vector" align="center">&gt;NAME</text>
<text x="0" y="0" size="1.016" layer="96" font="vector" ratio="15" align="center">&gt;VALUE</text>
</symbol>
<symbol name="MICROBUILDER_3.3V">
<wire x1="-1.27" y1="-1.27" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<pin name="3.3V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
<text x="-1.524" y="1.016" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="MICROBUILDER_GND">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
<text x="-1.524" y="-2.54" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="MICROBUILDER_SWITCH_TACT_SMT" prefix="SW" uservalue="yes">
<description>&lt;p&gt;SMT Tact Switches&lt;/p&gt;
&lt;ul&gt;
&lt;li&gt;6x6mm - Digikey: P12940SCT-ND&lt;/li&gt;
&lt;li&gt;KMR2 (4.6x2.8mm) - Digikey: 401-1426-1-ND&lt;/li&gt;
&lt;li&gt;EVQ-PQHB55 - Light Touch, 160GF (4.5x4.5mm) - Digikey: P8090SCT-ND&lt;/li&gt;
&lt;li&gt;KMT0 - KMT021 NGJ LHS (etc.) IP68/Waterproof - Digikey: CKN10289CT-ND&lt;/li&gt;
&lt;/ul&gt;</description>
<gates>
<gate name="G$1" symbol="MICROBUILDER_BUTTON_4PIN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MICROBUILDER_EVQ-Q2">
<connects>
<connect gate="G$1" pin="P" pad="A"/>
<connect gate="G$1" pin="P1" pad="A'"/>
<connect gate="G$1" pin="S" pad="B"/>
<connect gate="G$1" pin="S1" pad="B'"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="4.6X2.8" package="MICROBUILDER_BTN_KMR2_4.6X2.8">
<connects>
<connect gate="G$1" pin="P" pad="A"/>
<connect gate="G$1" pin="P1" pad="A'"/>
<connect gate="G$1" pin="S" pad="B"/>
<connect gate="G$1" pin="S1" pad="B'"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EVQPQ" package="MICROBUILDER_BTN_EVQPQ_4.5MM">
<connects>
<connect gate="G$1" pin="P" pad="A"/>
<connect gate="G$1" pin="P1" pad="C"/>
<connect gate="G$1" pin="S" pad="B"/>
<connect gate="G$1" pin="S1" pad="D"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KMT0" package="MICROBUILDER_BTN_KMT0">
<connects>
<connect gate="G$1" pin="P" pad="A"/>
<connect gate="G$1" pin="P1" pad="A'"/>
<connect gate="G$1" pin="S" pad="B"/>
<connect gate="G$1" pin="S1" pad="B'"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MICROBUILDER_RESISTOR" prefix="R" uservalue="yes">
<description>&lt;p&gt;&lt;b&gt;Resistors&lt;/b&gt;&lt;/p&gt;
&lt;p&gt;For new designs, use the packages preceded by an '_' character since they are more reliable:&lt;/p&gt;
&lt;p&gt;The following footprints should be used on most boards:&lt;/p&gt;
&lt;ul&gt;
&lt;li&gt;&lt;b&gt;_0402&lt;/b&gt; - Standard footprint for regular board layouts&lt;/li&gt;
&lt;li&gt;&lt;b&gt;_0603&lt;/b&gt; - Standard footprint for regular board layouts&lt;/li&gt;
&lt;li&gt;&lt;b&gt;_0805&lt;/b&gt; - Standard footprint for regular board layouts&lt;/li&gt;
&lt;li&gt;&lt;b&gt;_1206&lt;/b&gt; - Standard footprint for regular board layouts&lt;/li&gt;
&lt;/ul&gt;
&lt;p&gt;For extremely tight-pitch boards where space is at a premium, the following 'micro-pitch' footprints can be used (smaller pads, no silkscreen outline, etc.):&lt;/p&gt;
&lt;ul&gt;
&lt;li&gt;&lt;b&gt;_0402MP&lt;/b&gt; - Micro-pitch footprint for very dense/compact boards&lt;/li&gt;
&lt;li&gt;&lt;b&gt;_0603MP&lt;/b&gt; - Micro-pitch footprint for very dense/compact boards&lt;/li&gt;
&lt;li&gt;&lt;b&gt;_0805MP&lt;/b&gt; - Micro-pitch footprint for very dense/compact boards&lt;/li&gt;
&lt;li&gt;&lt;b&gt;_1206MP&lt;/b&gt; - Micro-pitch footprint for very dense/compact boards&lt;/li&gt;
&lt;/ul&gt;</description>
<gates>
<gate name="G$1" symbol="MICROBUILDER_RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="0603MINI" package="MICROBUILDER_0603-MINI">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805_NOOUTLINE" package="MICROBUILDER_0805-NO">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805_NOTHERMALS" package="MICROBUILDER_0805_NOTHERMALS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2012" package="MICROBUILDER_2012">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2512" package="MICROBUILDER_2512">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_0402" package="MICROBUILDER__0402">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_0402MP" package="MICROBUILDER__0402MP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_0603" package="MICROBUILDER__0603">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_0603MP" package="MICROBUILDER__0603MP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_0603_NOOUT" package="MICROBUILDER_0603-NO">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_0805" package="MICROBUILDER__0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_0805MP" package="MICROBUILDER__0805MP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_1206" package="MICROBUILDER__1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_1206MP" package="MICROBUILDER__1206MP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MICROBUILDER_3.3V">
<description>&lt;b&gt;3.3V Supply&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MICROBUILDER_3.3V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MICROBUILDER_GND">
<description>&lt;b&gt;GND&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MICROBUILDER_GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="Adafruit ESP8266 Feather" deviceset="MICROBUILDER_FRAME_A4" device=""/>
<part name="MS1" library="adafruit" deviceset="FEATHERWING" device=""/>
<part name="MS2" library="adafruit" deviceset="FEATHERWING" device="_NODIM"/>
<part name="SW_A" library="adafruit oled featherwing" deviceset="MICROBUILDER_SWITCH_TACT_SMT" device="KMT0"/>
<part name="SW_B" library="adafruit oled featherwing" deviceset="MICROBUILDER_SWITCH_TACT_SMT" device="KMT0"/>
<part name="SW_C" library="adafruit oled featherwing" deviceset="MICROBUILDER_SWITCH_TACT_SMT" device="KMT0"/>
<part name="R2" library="adafruit oled featherwing" deviceset="MICROBUILDER_RESISTOR" device="0603MINI" value="100k"/>
<part name="U$17" library="adafruit oled featherwing" deviceset="MICROBUILDER_3.3V" device="" value="3.3V"/>
<part name="U$18" library="adafruit oled featherwing" deviceset="MICROBUILDER_GND" device="" value="GND"/>
<part name="U$19" library="adafruit oled featherwing" deviceset="MICROBUILDER_GND" device="" value="GND"/>
<part name="U$20" library="adafruit oled featherwing" deviceset="MICROBUILDER_GND" device="" value="GND"/>
<part name="R6" library="adafruit oled featherwing" deviceset="MICROBUILDER_RESISTOR" device="0603MINI" value="3k"/>
<part name="R8" library="adafruit oled featherwing" deviceset="MICROBUILDER_RESISTOR" device="0603MINI" value="12k"/>
<part name="U$21" library="adafruit oled featherwing" deviceset="MICROBUILDER_GND" device="" value="GND"/>
<part name="S1" library="adafruit" deviceset="EG1213" device=""/>
<part name="U$22" library="Adafruit ESP8266 Feather" deviceset="MICROBUILDER_GND" device="" value="GND"/>
</parts>
<sheets>
<sheet>
<plain>
<text x="68.58" y="104.14" size="3.048" layer="91">ESP8266 Feather</text>
<text x="162.56" y="104.14" size="2.794" layer="91">OLED Featherwing</text>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="0" y="0"/>
<instance part="MS1" gate="G$1" x="68.58" y="101.6" rot="R270"/>
<instance part="MS2" gate="G$1" x="162.56" y="101.6" rot="R270"/>
<instance part="SW_A" gate="G$1" x="165.1" y="121.92"/>
<instance part="SW_B" gate="G$1" x="180.34" y="121.92"/>
<instance part="SW_C" gate="G$1" x="218.44" y="121.92"/>
<instance part="R2" gate="G$1" x="205.74" y="119.38" rot="R90"/>
<instance part="U$17" gate="G$1" x="205.74" y="127"/>
<instance part="U$18" gate="G$1" x="160.02" y="116.84"/>
<instance part="U$19" gate="G$1" x="175.26" y="116.84"/>
<instance part="U$20" gate="G$1" x="213.36" y="116.84"/>
<instance part="R6" gate="G$1" x="50.8" y="137.16"/>
<instance part="R8" gate="G$1" x="60.96" y="137.16"/>
<instance part="U$21" gate="G$1" x="43.18" y="137.16" rot="R270"/>
<instance part="S1" gate="1" x="132.08" y="81.28" rot="MR270"/>
<instance part="U$22" gate="G$1" x="124.46" y="78.74" rot="R270"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$26" class="0">
<segment>
<pinref part="SW_A" gate="G$1" pin="S1"/>
<junction x="170.18" y="119.38"/>
<pinref part="SW_A" gate="G$1" pin="S"/>
<wire x1="170.18" y1="119.38" x2="170.18" y2="121.92" width="0.1524" layer="91"/>
<wire x1="170.18" y1="119.38" x2="170.18" y2="111.76" width="0.1524" layer="91"/>
<wire x1="170.18" y1="111.76" x2="203.2" y2="111.76" width="0.1524" layer="91"/>
<wire x1="203.2" y1="111.76" x2="203.2" y2="68.58" width="0.1524" layer="91"/>
<pinref part="MS2" gate="G$1" pin="GPIO9"/>
<junction x="200.66" y="68.58"/>
<wire x1="203.2" y1="68.58" x2="200.66" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="SW_B" gate="G$1" pin="S1"/>
<junction x="185.42" y="119.38"/>
<wire x1="185.42" y1="119.38" x2="185.42" y2="114.3" width="0.1524" layer="91"/>
<wire x1="185.42" y1="114.3" x2="205.74" y2="114.3" width="0.1524" layer="91"/>
<wire x1="205.74" y1="114.3" x2="205.74" y2="66.04" width="0.1524" layer="91"/>
<pinref part="MS2" gate="G$1" pin="GPIO6"/>
<junction x="200.66" y="66.04"/>
<wire x1="205.74" y1="66.04" x2="200.66" y2="66.04" width="0.1524" layer="91"/>
<junction x="205.74" y="114.3"/>
<pinref part="R2" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="SW_C" gate="G$1" pin="S1"/>
<junction x="223.52" y="119.38"/>
<wire x1="223.52" y1="119.38" x2="223.52" y2="63.5" width="0.1524" layer="91"/>
<pinref part="MS2" gate="G$1" pin="GPIO5"/>
<junction x="200.66" y="63.5"/>
<wire x1="223.52" y1="63.5" x2="200.66" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="3.3V" class="0">
<segment>
<pinref part="R2" gate="G$1" pin="2"/>
<pinref part="U$17" gate="G$1" pin="3.3V"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="SW_A" gate="G$1" pin="P1"/>
<junction x="160.02" y="119.38"/>
<pinref part="U$18" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SW_B" gate="G$1" pin="P1"/>
<junction x="175.26" y="119.38"/>
<pinref part="U$19" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="SW_C" gate="G$1" pin="P1"/>
<junction x="213.36" y="119.38"/>
<pinref part="U$20" gate="G$1" pin="GND"/>
</segment>
<segment>
<pinref part="R6" gate="G$1" pin="1"/>
<pinref part="U$21" gate="G$1" pin="GND"/>
<junction x="45.72" y="137.16"/>
</segment>
<segment>
<pinref part="S1" gate="1" pin="S"/>
<pinref part="U$22" gate="G$1" pin="GND"/>
<junction x="127" y="78.74"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="MS1" gate="G$1" pin="GPIOSCL"/>
<junction x="106.68" y="60.96"/>
<wire x1="106.68" y1="60.96" x2="111.76" y2="60.96" width="0.1524" layer="91"/>
<wire x1="111.76" y1="60.96" x2="111.76" y2="50.8" width="0.1524" layer="91"/>
<wire x1="111.76" y1="50.8" x2="203.2" y2="50.8" width="0.1524" layer="91"/>
<wire x1="203.2" y1="50.8" x2="203.2" y2="60.96" width="0.1524" layer="91"/>
<pinref part="MS2" gate="G$1" pin="GPIOSCL"/>
<junction x="200.66" y="60.96"/>
<wire x1="203.2" y1="60.96" x2="200.66" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="MS1" gate="G$1" pin="GPIOSDA"/>
<junction x="106.68" y="58.42"/>
<wire x1="106.68" y1="58.42" x2="106.68" y2="48.26" width="0.1524" layer="91"/>
<wire x1="106.68" y1="48.26" x2="200.66" y2="48.26" width="0.1524" layer="91"/>
<pinref part="MS2" gate="G$1" pin="GPIOSDA"/>
<junction x="200.66" y="58.42"/>
<wire x1="200.66" y1="48.26" x2="200.66" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$30" class="0">
<segment>
<pinref part="MS1" gate="G$1" pin="!RESET"/>
<junction x="63.5" y="96.52"/>
<wire x1="63.5" y1="96.52" x2="63.5" y2="114.3" width="0.1524" layer="91"/>
<pinref part="MS2" gate="G$1" pin="!RESET"/>
<wire x1="63.5" y1="114.3" x2="157.48" y2="114.3" width="0.1524" layer="91"/>
<wire x1="157.48" y1="114.3" x2="157.48" y2="96.52" width="0.1524" layer="91"/>
<junction x="157.48" y="96.52"/>
</segment>
</net>
<net name="3V" class="0">
<segment>
<pinref part="MS1" gate="G$1" pin="3V"/>
<junction x="63.5" y="93.98"/>
<wire x1="63.5" y1="93.98" x2="60.96" y2="93.98" width="0.1524" layer="91"/>
<wire x1="60.96" y1="93.98" x2="60.96" y2="116.84" width="0.1524" layer="91"/>
<wire x1="60.96" y1="116.84" x2="154.94" y2="116.84" width="0.1524" layer="91"/>
<wire x1="154.94" y1="116.84" x2="154.94" y2="93.98" width="0.1524" layer="91"/>
<pinref part="MS2" gate="G$1" pin="3V"/>
<wire x1="154.94" y1="93.98" x2="157.48" y2="93.98" width="0.1524" layer="91"/>
<junction x="157.48" y="93.98"/>
</segment>
</net>
<net name="VBAT" class="0">
<segment>
<pinref part="MS1" gate="G$1" pin="VBAT"/>
<junction x="106.68" y="86.36"/>
<wire x1="106.68" y1="86.36" x2="106.68" y2="137.16" width="0.1524" layer="91"/>
<pinref part="R8" gate="G$1" pin="2"/>
<junction x="66.04" y="137.16"/>
<wire x1="106.68" y1="137.16" x2="66.04" y2="137.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="R6" gate="G$1" pin="2"/>
<pinref part="R8" gate="G$1" pin="1"/>
<junction x="55.88" y="137.16"/>
<wire x1="55.88" y1="137.16" x2="55.88" y2="91.44" width="0.1524" layer="91"/>
<pinref part="MS1" gate="G$1" pin="AREF"/>
<junction x="63.5" y="91.44"/>
<wire x1="55.88" y1="91.44" x2="63.5" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="MS1" gate="G$1" pin="EN"/>
<junction x="106.68" y="83.82"/>
<pinref part="S1" gate="1" pin="O"/>
<junction x="127" y="83.82"/>
<wire x1="106.68" y1="83.82" x2="127" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
