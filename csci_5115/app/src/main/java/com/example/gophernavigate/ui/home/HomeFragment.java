package com.example.gophernavigate.ui.home;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SearchView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import com.example.gophernavigate.NavigateActivity;
import com.example.gophernavigate.R;
import com.example.gophernavigate.StepsActivity;
import com.google.android.gms.maps.CameraUpdate;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.GoogleMap.OnMapClickListener;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;

public class HomeFragment extends Fragment  implements OnMapReadyCallback, OnMapClickListener {

    private HomeViewModel homeViewModel;
    private ListView list;
    private GoogleMap mMap;
    private Marker marker;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {
        homeViewModel =
                ViewModelProviders.of(this).get(HomeViewModel.class);
        View root = inflater.inflate(R.layout.fragment_home, container, false);

        SupportMapFragment mapFragment = (SupportMapFragment) getChildFragmentManager().findFragmentById(R.id.map);
        if (mapFragment != null) {
            mapFragment.getMapAsync(this);
        } else {
            Log.println    (Log.INFO,"wut","can't load map");
        }

        final SearchView search = root.findViewById(R.id.search_bar);
        list = root.findViewById(R.id.search_list);


        search.setOnSearchClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                return;
            }
        });
        search.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String query) {
//                if (mMap != null) {
//                    mMap.addMarker(new MarkerOptions().position(marker.getPosition()).title(query));
//                }
                Intent intent = new Intent(getContext(), NavigateActivity.class);
//                Intent intent = new Intent(getContext(), StepsActivity.class);

                startActivity(intent);
                return false;
            }

            @Override
            public boolean onQueryTextChange(String newText) {
                return false;
            }
        });


//        final TextView textView = root.findViewById(R.id.text_home);
//        homeViewModel.getText().observe(this, new Observer<String>() {
//            @Override
//            public void onChanged(@Nullable String s) {
//                textView.setText(s);
//            }
//        });
        return root;
    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        Log.println    (Log.INFO,"wut","loaded map");
        mMap = googleMap;

        // Add a marker in Sydney and move the camera
        LatLng sydney = new LatLng(44.975100, -93.234510);
        marker = mMap.addMarker(new MarkerOptions().position(sydney).title("Current Position"));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(sydney, 15));
        mMap.setOnMapClickListener(this);

    }

    @Override
    public void onMapClick(LatLng pos) {
//        mMap.addMarker(new MarkerOptions().position(pos));
//        mMap.addMarker()
        marker.setPosition(pos);
        Log.d("debug", pos.toString());
    }
}