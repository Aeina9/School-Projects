package com.example.gophernavigate;

import androidx.annotation.Nullable;

import androidx.fragment.app.FragmentActivity;
import androidx.core.content.ContextCompat;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.BitmapDescriptor;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;


import java.util.ArrayList;
import java.util.List;

public class NavigateActivity extends FragmentActivity implements OnMapReadyCallback, GoogleMap.OnMapClickListener {

    private GoogleMap mMap;
    private Polyline outline;
    private Polyline inline;
    private List<LatLng> outdoor;
    private List<LatLng> indoor;
    private boolean isOutdoor = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_navigate);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);

        outdoor = new ArrayList<LatLng>();
        outdoor.add(new LatLng(44.973857657981334,-93.2334079965949));
        outdoor.add(new LatLng(44.974022500741775,-93.23375534266232));
        outdoor.add(new LatLng(44.97410812391668,-93.23378853499891));
        outdoor.add(new LatLng(44.97409413011017,-93.23211751878262));
        outdoor.add(new LatLng(44.974386576238764,-93.23224056512119));
        outdoor.add(new LatLng(44.97439108269624,-93.23211751878262));

        indoor = new ArrayList<LatLng>();
        indoor.add(new LatLng(44.973857657981334,-93.2334079965949));
        indoor.add(new LatLng(44.973857657981334,-93.23220770806074));
        indoor.add(new LatLng(44.97428695972012,-93.23211751878262));
        indoor.add(new LatLng(44.974386576238764,-93.23224056512119));
        indoor.add(new LatLng(44.97439108269624,-93.23211751878262));

        final TextView eta = (TextView) findViewById(R.id.eatText);
        eta.setText("ETA: 5 Minutes");

        Button start = (Button) findViewById(R.id.button3);
        final Context ctx = this;
        start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ctx, StepsActivity.class);
                intent.putExtra("Outdoor",isOutdoor);
                startActivityForResult(intent, RESULT_OK);
            }
        });


        Button inbutton = (Button) findViewById(R.id.inbutton);
        inbutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                inline.setColor(0xFF0000FF);
                outline.setColor(0x55FF0000);
                isOutdoor = false;
                eta.setText("ETA: 6 Minutes");
                Log.d("debug","Indoor selected");
            }
        });

        Button outbutton = (Button) findViewById(R.id.outbutton);
        outbutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                inline.setColor(0x550000FF);
                outline.setColor(0xFFFF0000);
                isOutdoor = true;
                eta.setText("ETA: 5 Minutes");
                Log.d("debug","Outdoor selected");
            }
        });
    }

    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */

    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        // Add a marker in Sydney and move the camera
        LatLng startPt = new LatLng(44.973807657981334,-93.2334079965949);
        mMap.addMarker(new MarkerOptions().position(startPt).title("Current Location")
                       .icon(BitmapFromVector(getApplicationContext(), R.drawable.ic_start_location)));

        LatLng endPt = new LatLng(44.97439108269624,-93.23211751878262);
        mMap.addMarker(new MarkerOptions().position(endPt).title("Destination")
                       .icon(BitmapFromVector(getApplicationContext(), R.drawable.ic_end_location)));

        LatLng midPt = new LatLng((44.973807657981334+44.97439108269624)/2,
                                  (-93.2334079965949+-93.23211751878262)/2);

        outline = mMap.addPolyline(new PolylineOptions().addAll(outdoor).color(0xffff0000));
        inline = mMap.addPolyline(new PolylineOptions().addAll(indoor).color(0x550000ff));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(midPt, 18));
        mMap.setOnMapClickListener(this);
    }

    private BitmapDescriptor BitmapFromVector(Context context, int vectorResId) {
        // below line is use to generate a drawable.
        Drawable vectorDrawable = ContextCompat.getDrawable(context, vectorResId);

        // below line is use to set bounds to our vector drawable.
        vectorDrawable.setBounds(0, 0, vectorDrawable.getIntrinsicWidth(), vectorDrawable.getIntrinsicHeight());

        // below line is use to create a bitmap for our
        // drawable which we have added.
        Bitmap bitmap = Bitmap.createBitmap(vectorDrawable.getIntrinsicWidth(), vectorDrawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);

        // below line is use to add bitmap in our canvas.
        Canvas canvas = new Canvas(bitmap);

        // below line is use to draw our
        // vector drawable in canvas.
        vectorDrawable.draw(canvas);

        // after generating our bitmap we are returning our bitmap.
        return BitmapDescriptorFactory.fromBitmap(bitmap);
    }

    @Override
    public void onMapClick(LatLng pos) {
//        mMap.addMarker(new MarkerOptions().position(pos));
//        mMap.addMarker()
//        List<LatLng> points = outline.getPoints();
//        points.add(pos);
//        outline.setPoints(points);
        Log.d("debug", pos.toString());
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        Log.d("debug","scanning activity result");
        if (resultCode == Activity.RESULT_OK) {
            finish();
        }
    }
}