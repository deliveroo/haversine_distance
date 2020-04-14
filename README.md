# Haversine distance

Just a simple gem to compute Haversine Distance in C


## Usage

Add to your Gemfile:

```
gem 'haversine_distance_c', '~> 0.0.2'
```

Then:

```
meters = HaversineDistance.m(point_a.lat,point_a.long,point_b.lat,point_b.long)
km = HaversineDistance.km(point_a.lat,point_a.long,point_b.lat,point_b.long)
```

## Development

```
$ rake compile
$ rake spec
$ rake build
```
