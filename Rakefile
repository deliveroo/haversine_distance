require './lib/haversine_distance/version'
require 'fileutils'
require 'English'

task :config do
  def version
    HaversineDistance::VERSION
  end
  # e.g. 2.13.3 becomes HaversineDistance__2-13-3
  def version_tag
    "HaversineDistance_#{version.gsub('.','-')}"
  end
  # e.g. 2.13.3 becomes haversine_distance_-2.13.3.gem
  def gem_name
    "haversine_distance_c-#{version}.gem"
  end

  def base
    File.expand_path('..', __FILE__)
  end
end

desc 'abort when repo is not clean or has uncommited code'
task :assert_clean_repo do
  sh('git diff --exit-code')
  abort 'Git repo not clean' unless $CHILD_STATUS.success?
  sh('git diff-index --quiet --cached HEAD')
  abort 'Git repo not commited' unless $CHILD_STATUS.success?
end

desc 'build gem'
task :build => [:config] do
  sh 'gem build -V haversine_distance_c.gemspec'
  if $CHILD_STATUS.success?
    FileUtils.mkdir_p(File.join(base, 'pkg'))
    FileUtils.mv(File.join(base, gem_name), 'pkg')
  else
    STDERR.puts 'Could not build gem'
    exit $CHILD_STATUS.exitstatus
  end
end

task :push_and_tag => [:build] do
  sh "gem push #{File.join(base, 'pkg', gem_name)}"
  if $CHILD_STATUS.success?
    sh "git tag -a -m \"Version #{version}\" #{version_tag}"
    STDOUT.puts "Tagged #{version_tag}."
    sh 'git push'
    sh 'git push --tags'
  else
    abort 'tagging aborted pushing gem failed'
  end
end

desc 'Release'
task :release => [:assert_clean_repo, :push_and_tag]

desc 'Release and build the legacy way'
task :legacy_release=> ['legacy:README.html', 'legacy:extconf', 'legacy:doc', 'legacy:manifest', 'release']


require 'rake/extensiontask'
require 'rake/testtask'
require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec)

Rake::ExtensionTask.new('haversine_distance') do |ext|
  ext.ext_dir = 'ext/haversine_distance_c'
end

Rake::TestTask.new(:test) do |t|
  t.libs << 'test'
end

task :test => :compile
task :spec => :compile
