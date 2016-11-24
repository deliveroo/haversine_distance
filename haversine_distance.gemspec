require './lib/haversine_distance/version'


Gem::Specification.new do |s|
  s.name = 'haversine_distance'
  s.version = HaversineDistance::VERSION
  s.date = Date.today.to_s
  s.summary = 'C calculation of the Haversine Distance'
  s.description = 'Calculates the distance between two points using the haversine distance'
  s.authors = ['Ivan Pirlik']
  s.email = 'ivan.pirlik@deliveroo.co.uk'
  s.license = 'MIT'

  tracked_files = `git ls-files`.split($OUTPUT_RECORD_SEPARATOR)
  file_exclusion_regex = %r{(\Alib/rvg/to_c.rb)}
  files         = tracked_files.reject{|file| file[file_exclusion_regex] }
  test_files    = files.grep(%r{^(test|spec|features)/})

  s.files                       = files
  s.test_files                  = test_files
  s.require_paths << 'ext'

  s.extensions = %w{ext/haversine_distance/extconf.rb}
  s.has_rdoc = false

  s.add_development_dependency 'rake-compiler'
  s.add_development_dependency 'rspec', '~> 3.2.0'
end
