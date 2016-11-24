require 'haversine_distance'
require 'byebug'

describe HaversineDistance do
  describe '.km' do
    let(:point1) { [ -0.141833514017446, 51.4956699956174 ] }
    let(:point2) { [ -0.171055, 51.485144 ] }

    context 'when lat-long for both points are same' do
      it do
       expect(described_class.km(point1[0], point1[1], point1[0], point1[1])).to eql(0.0)
     end
    end

    context 'when lat-long for both points are not same' do
      it { expect(described_class.km(point1[0], point1[1], point2[0], point2[1]).round(2)).to eql(3.45) }
    end
  end

  describe '.m' do
    let(:point1) { [ -0.141833514017446, 51.4956699956174 ] }
    let(:point2) { [ -0.171055, 51.485144 ] }
    let(:precision) { 2 }

    context 'when lat-long for both points are not same' do
      it { expect(described_class.m(point1[0], point1[1], point2[0], point2[1]).round(2)).to eql(3453.66) }
    end
  end
end
