#include <chrono>
#include <cstdlib>
#include <gtk/gtk.h>
#include <iostream>
#include <iterator>
#include <string>
#include <unistd.h>
#include <vector>

#include "Animation.h"
#include "ConfigReader.h"
#include "Controls.h"
#include "Direction.h"
#include "Entity.h"
#include "GravitySimulation.h"
#include "LegalDistances.h"
#include "MapCollisionHandling.h"
#include "MapLoader.h"

using namespace std;
using namespace chrono;
using std::begin;
using std::end;

static gint64 oldTime = 0;
static gint64 newTime = 0;

struct mapDimensions {
  float dimX = 800;
  float dimY = 800;
  float dimZ = 800;
};

static GravitySimulation gSim(9.8, 2.0);
static Controls controls(ConfigReader::getConfig("keys-default.properties"));
static Entity myPlayer(100, 50, 50, 75, 10, 10, 10);
static Entity myBox(200.0, 80.0, 50.0, 10, 30, 30, 30);
static Entity myBox2(350.0, 200.0, 50.0, 10, 30, 30, 30);
static vector<Entity> myMapEntities;
static mapDimensions gameMap;
static MapCollisionHandling mapCollisionHandling(gameMap.dimX, gameMap.dimY,
                                                 gameMap.dimZ);
static Animation jumpUp(0, 0, 0, 0, 0);

static GtkWidget *area;

static void handle_key_pressed(GtkEventControllerKey *self, guint keyval,
                               guint keycode, GdkModifierType state,
                               gpointer user_data) {
  g_print("Press from key %d\n", keycode);

  controls.press(keycode);
}

static void handle_key_released(GtkEventControllerKey *self, guint keyval,
                                guint keycode, GdkModifierType state,
                                gpointer user_data) {
  controls.release(keycode);
}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width,
                          int height, gpointer data) {
  cairo_rectangle(cr, myPlayer.getX() - myPlayer.getDimX(),
                  height - myPlayer.getY() - myPlayer.getDimY(),
                  myPlayer.getDimX() * 2, myPlayer.getDimY() * 2);
  for (int i = 0; i < 2; i++) {
    Entity e = myMapEntities.at(i);
    cairo_rectangle(cr, e.getX() - e.getDimX(),
                    height - e.getY() - e.getDimY(), e.getDimX() * 2,
                    e.getDimY() * 2);
  }
  cairo_set_source_rgb(cr, 0.7, 0.4, 0.6);

  cairo_fill(cr);
}

static gboolean handle_tick(GtkWidget *widget, GdkFrameClock *frame_clock,
                            gpointer user_data) {
  newTime = gdk_frame_clock_get_frame_time(frame_clock);

  if (newTime - oldTime > 33332) {
    LegalDistances legalDistances =
        mapCollisionHandling.getLegalMovement(&myPlayer, myMapEntities, myMapEntities.size());

    if (controls.isPressed("SPACE")) {
      float maxFlyDistance =
          mapCollisionHandling.getMaxFlyDistance(&myPlayer, myMapEntities, myMapEntities.size());
      if (jumpUp.attemptFinish(&myPlayer) && !myPlayer.isFalling()) {
        jumpUp = Animation(0, myPlayer.getY(), 0,
                           myPlayer.getY() +
                               (150 < maxFlyDistance ? 150 : maxFlyDistance),
                           20);
      }
    }
    if (controls.isPressed("LEFT")) {
      float oldX = myPlayer.getX();
      myPlayer.move(Direction::XBACKW, 8);
      if (mapCollisionHandling.colliding(&myPlayer, myMapEntities, myMapEntities.size())) {
        myPlayer.setX(oldX);
      }
    }
    if (controls.isPressed("RIGHT")) {
      float oldX = myPlayer.getX();
      myPlayer.move(Direction::XFORW, 8);
      if (mapCollisionHandling.colliding(&myPlayer, myMapEntities, myMapEntities.size())) {
        myPlayer.setX(oldX);
      }
    }
    if (controls.isPressed("DOWN")) {
      float oldZ = myPlayer.getZ();
      myPlayer.move(Direction::ZBACKW, 8);
      if (mapCollisionHandling.colliding(&myPlayer, myMapEntities, myMapEntities.size())) {
        myPlayer.setZ(oldZ);
      }
    }
    if (controls.isPressed("UP")) {
      float oldZ = myPlayer.getZ();
      myPlayer.move(Direction::ZFORW, 8);
      if (mapCollisionHandling.colliding(&myPlayer, myMapEntities, myMapEntities.size())) {
        myPlayer.setZ(oldZ);
      }
    }

    if (!jumpUp.isFinished()) {
      g_print("Player X: %f, Y: %f \n", myPlayer.getX(), myPlayer.getY());
      myPlayer.fly(jumpUp.getY(&myPlayer) - myPlayer.getY());
    }

    float maxFallDistance =
        mapCollisionHandling.getMaxFallDistance(&myPlayer, myMapEntities, myMapEntities.size());
    if (maxFallDistance > 0) {
      myPlayer.setFalling(true);
    }

    float fallDistance = 0;
    if (myPlayer.isFalling()) {
      g_print("New time: %d Old time: %d\n", newTime, oldTime);
      float seconds =
          (myPlayer.getFallTime() + (newTime - oldTime) / 1000000.0);
      g_print("Fall seconds added: %f\n", seconds);
      // float simFallDistance = gSim.getDistance(seconds, myPlayer.getMass());
      float simFallDistance = gSim.getDistance(seconds);
      simFallDistance = simFallDistance < 0 ? 0 : simFallDistance;
      fallDistance =
          simFallDistance < maxFallDistance ? simFallDistance : maxFallDistance;
      if (fallDistance <= 0) {
        myPlayer.stopFalling();
      } else {
        myPlayer.fall(myPlayer.getFallTime() + seconds, fallDistance);
      }
    }
    gtk_widget_queue_draw(area);
    oldTime = newTime;
  }

  return G_SOURCE_CONTINUE;
}

static void activate(GtkApplication *app, gpointer user_data) {
  //myMapEntities.push_back(myBox);
  //myMapEntities.push_back(myBox2);
  myMapEntities = MapLoader::getMapEntities("maps/map1.smap");
  myPlayer = MapLoader::getPlayerEntities("maps/map1.smap").at(0);
  //myMapEntities = mapEntities;
  //myPlayer = playerEntities[0];

  GtkWidget *window;

  GtkEventController *keyCtrl;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Simple Arena");
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);

  area = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(area), 800);
  gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(area), 800);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), draw_function, NULL,
                                 NULL);
  gtk_widget_set_valign(area, GtkAlign::GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(window), area);

  keyCtrl = gtk_event_controller_key_new();
  g_signal_connect(keyCtrl, "key-pressed", G_CALLBACK(handle_key_pressed),
                   NULL);
  g_signal_connect(keyCtrl, "key-released", G_CALLBACK(handle_key_released),
                   NULL);
  gtk_widget_add_controller(window, keyCtrl);

  gtk_widget_add_tick_callback(window, handle_tick, NULL, NULL);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.flikkes.simplearena",
                            G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
