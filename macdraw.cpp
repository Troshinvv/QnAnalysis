//
// Created by mikhail on 5/6/21.
//

void macdraw(){
  gROOT->Macro( "/home/valeriy/flow_drawing_tools/example/style.cc" );
  auto leg1 = new TLegend( 0.5, 0.75, 0.9, 0.945 );
 // auto leg2 = new TLegend( 0.5, 0.65, 0.9, 0.75 );

  auto v1_bw_x = DoubleDifferentialCorrelation( "~/correlation_out.root",
                                              {
                                                 "uQ/protons_PLAIN.fhcalN_RECENTERED.x1y1",
                                             } );
  v1_bw_x.SetSliceVariable("Eta", "");
  v1_bw_x.SetMarker(kFullCircle);
  v1_bw_x.SetPalette( {kOrange+1, kSpring-4, kGreen+2, kAzure-4, kRed, kViolet, kBlue } );
  v1_bw_x.Select({{"McEvent._B", 4, 4, 8}});
  v1_bw_x.SetProjectionAxis({"TpcTracks._pT", 10,0.2,2.});
  v1_bw_x.SetSliceAxis({"TpcTracks._eta", {0.,1.}});
  v1_bw_x.Calculate();

  auto v1_bw_y = DoubleDifferentialCorrelation( "~/correlation_out.root",
                                              {
                                                 "uQ/protons_PLAIN.fhcalN_RECENTERED.y1x1",
                                             } );
  v1_bw_y.SetSliceVariable("Eta", "");
  v1_bw_y.SetMarker(kOpenSquare);
  v1_bw_y.SetPalette( {kOrange+1, kSpring-4, kGreen+2, kAzure-4, kRed, kViolet, kBlue } );
  v1_bw_y.Select({{"McEvent._B", 4, 4, 8}});
  v1_bw_y.SetProjectionAxis({"TpcTracks._pT", 10, 0.2, 2.});
  v1_bw_y.SetSliceAxis({"TpcTracks._eta", {0.,1.}});
  v1_bw_y.Calculate();

  HeapPicture pic( "_corrected_y_slices_pT", {1000, 1000});

  pic.AddText({0.2, 0.9, "MPD Au+Au@7.7A GeV"}, 0.025);
  pic.AddText({0.2, 0.87, "#p;u_{1}Q_{1} "}, 0.025);
  pic.AddText({0.2, 0.84, "XY-FullCircle;YX-OpenSquare"}, 0.025);
 /* pic.AddText({0.2, 0.81, "SP: #LTu_{1}W1#GT"}, 0.025);
  pic.AddText({0.2, 0.78, "w/o occ. corr."}, 0.025); */

  for( auto obj : v1_bw_x.GetProjections() ){
    pic.AddDrawable( obj );
    leg1->AddEntry( obj->GetPoints(), obj->GetTitle().c_str(), "P" );
  }
  for( auto obj : v1_bw_y.GetProjections() ){
    pic.AddDrawable( obj );
  }
/*  leg2->AddEntry( v1_bw_x.GetProjections().at(2)->GetPoints(), "XY", "P" );
  leg2->AddEntry( v1_bw_y.GetProjections().at(2)->GetPoints(), "YX", "P" ); */

  pic.SetAxisTitles({"Eta", "u_{1}Q_{1}"});
  pic.AddLegend(leg1);
//  pic.AddLegend(leg2);

  pic.SetXRange({0.2, 2.});
  pic.SetYRange({-0.0005, 0.0005});
  pic.Draw();
  pic.Save("/home/valeriy/HistoQn/pNyxxypT","png");
}
